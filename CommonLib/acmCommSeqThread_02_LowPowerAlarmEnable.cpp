/*==============================================================================
Detestion:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "cmnProgramParms.h"
#include "smShare.h"
#include "acmCommSeqThread.h"

namespace ACM
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// For the individual settings variable, process the super settings
// as follows:
//
// If the tx flag is true then then send a command to the acm to set the
// variable, based on the tx variable. Receive and process the response
// to set the rx and qx variables. 
//
// If the tx flag is false then send a command to the acm to read the
// current variable. Receive and process the response to set the rx
// variable.

void CommSeqThread::txrxLowPowerAlarmEnable(bool aTxFlag)
{
	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Send a command to the acm.

		// Do this first.
	ACM::SuperSettingsACM* tS = &SM::gShare->mSuperSettingsACM;
	tS->mQxLowPowerAlarmEnable = cQx_Pending2;

	// Format the command string.
	char tBuffer[200];
	if (aTxFlag)
	{
		// Command to write the variable.
		sprintf(tBuffer, "G%1d", tS->mTxLowPowerAlarmEnable);
	}
	else
	{
		// Command to read the variable.
		sprintf(tBuffer, "BT");
	}

	// Set the thread notification mask.
	mNotify.setMaskOne("CmdAck", cCmdAckNotifyCode);

	// Send the command.
	sendString(tBuffer);

	// Wait for the receive acknowledgement notification.
	mNotify.wait(cCmdAckTimeout);

	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Process the response from the acm.

		// Read the receive string from the queue.
	std::string* tRxString = mRxStringQueue.tryRead();
	if (tRxString == 0)
	{
		Prn::print(Prn::View11, "RxQueue EMPTY");
		return;
	}

	// Point to the first char in the response string that is not '>'.
	int tRet = 0;
	const char* tResponse;
	if (tRxString->c_str()[0] != '>') tResponse = &tRxString->c_str()[0];
	else                              tResponse = &tRxString->c_str()[1];

	// Temp variables to be extracted from the response string.
	int   tV = 0;
	bool tTxLowPowerAlarmEnable = tS->mTxLowPowerAlarmEnable;
	bool tRxLowPowerAlarmEnable = false;

	// 012345678901234
	// L=32768

	// Guard.
	if ((tResponse[0] != 'L') ||
		(tResponse[1] != '=') ||
		(tResponse[7] != 0)
		)
	{
		Prn::print(Prn::View21, "txrxLowPowerAlarmEnable ERROR 101 %s", tResponse);
		delete tRxString;
		return;
	}

	// Read from response string into temp variables.
	tRet = sscanf(tResponse, "L=%d",
		&tV);

	// Guard.
	if (tRet != 1)
	{
		delete tRxString;
		Prn::print(Prn::View21, "txrxLowPowerAlarmEnable ERROR 102");
	}

	// Convert.
	tRxLowPowerAlarmEnable = tV & 0x8000;

	// If rx only then done. Copy the temp to the settings and exit.
	if (!aTxFlag)
	{
		Prn::print(Prn::View21, "LowPowerAlarmEnable %sf",
			my_string_from_bool(tRxLowPowerAlarmEnable));
		tS->mRxLowPowerAlarmEnable = tRxLowPowerAlarmEnable;
		delete tRxString;
		return;
	}

	// Compare.
	if (tTxLowPowerAlarmEnable == tRxLowPowerAlarmEnable)
	{
		// If ok then copy the temp to the member and set the
		// qx ack code for an ack. 
		tS->mRxLowPowerAlarmEnable = tRxLowPowerAlarmEnable;
		tS->mQxLowPowerAlarmEnable = cQx_Ack;
	}
	else
	{
		// If not ok then set the qx ack code for a nak. 
		tS->mQxLowPowerAlarmEnable = cQx_Nak;
	}

	Prn::print(Prn::View21, "LowPowerAlarmEnable %s %s",
		asString_Qx(tS->mQxLowPowerAlarmEnable), my_string_from_bool(tRxLowPowerAlarmEnable));

	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Done.

	delete tRxString;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace