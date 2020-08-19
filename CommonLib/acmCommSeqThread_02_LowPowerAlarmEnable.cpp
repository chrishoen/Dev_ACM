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
	ACM::SuperStateACM* tX = &SM::gShare->mSuperStateACM;
	tS->mQxLowPowerAlarmEnable = cQx_Pending2;

	// Format the command string.
	char tTxString[100];
	if (aTxFlag)
	{
		// Cmmand to write the variable.
		sprintf(tTxString, "G%1d", tS->mTxLowPowerAlarmEnable);
	}
	else
	{
		// Command to read the variable. This sends to commands, because
		// of protocol goofiness. The response for the second will be ignored.
		sprintf(tTxString, "BD");
	}

	// Set the thread notification mask.
	mNotify.setMaskOne("CmdAck", cCmdAckNotifyCode);

	// Send the command.
	sendString(tTxString);

	// Wait for the receive response notification.
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
		tS->mQxLowPowerAlarmEnable = cQx_Nak;
		delete tRxString;
		return;
	}

	// Point to the first char in the response string that is not '>'.
	int tRet = 0;
	const char* tResponse;
	if (tRxString->c_str()[0] != '>') tResponse = &tRxString->c_str()[0];
	else                              tResponse = &tRxString->c_str()[1];

	// Temp variables to be extracted from the response string.
	int  tV = 0;
	bool tTxLowPowerAlarmEnable = tS->mTxLowPowerAlarmEnable;
	bool tRxLowPowerAlarmEnable = false;

	// 012345678901234
	// L=32768           for tx
	// 01ffclL=32768     for rx

	// If txrx.
	if (aTxFlag)
	{
		// Read from response string into temp variables.
		tRet = sscanf(tResponse, "L=%d",
			&tV);

		// Guard.
		if (tRet != 1)
		{
			Prn::print(Prn::View21, "LowPowerAlarmEnable             Nak ERROR 102 %s", tResponse);
			tS->mQxLowPowerThresh_pct = cQx_Nak;
			delete tRxString;
			return;
		}

		// Convert.
		tRxLowPowerAlarmEnable = tV & 0x8000;
		tX->mLowPowerAlarmEnable = tRxLowPowerAlarmEnable;
	}
	// If rx only.
	else
	{
		// Read from response string into temp variables.
		tRet = sscanf(tResponse, "%x",
			&tV);

		// Guard.
		if (tRet != 1)
		{
			Prn::print(Prn::View21, "LowPowerAlarmEnable             Nak ERROR 102 %s", tResponse);
			tS->mQxLowPowerThresh_pct = cQx_Nak;
			delete tRxString;
			return;
		}

		// Convert.
		tRxLowPowerAlarmEnable = tV & 0x0020;
	}

	// Compare.
	if (!aTxFlag || tTxLowPowerAlarmEnable == tRxLowPowerAlarmEnable)
	{
		// If rx only or compare ok then copy the temp to the rx variable
		// and set the qx ack code for an ack. 
		tS->mRxLowPowerAlarmEnable = tRxLowPowerAlarmEnable;
		tS->mQxLowPowerAlarmEnable = cQx_Ack;
	}
	else
	{
		// If not ok then set the qx ack code for a nak. 
		tS->mQxLowPowerAlarmEnable = cQx_Nak;
	}

	Prn::print(Prn::View21, "LowPowerAlarmEnable         %s %s",
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