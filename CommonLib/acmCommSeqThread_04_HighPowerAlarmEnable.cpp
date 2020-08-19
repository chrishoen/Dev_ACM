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

void CommSeqThread::txrxHighPowerAlarmEnable(bool aTxFlag)
{
	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Send a command to the acm.

		// Do this first.
	ACM::SuperSettingsACM* tS = &SM::gShare->mSuperSettingsACM;
	ACM::SuperStateACM* tX = &SM::gShare->mSuperStateACM;
	tS->mQxHighPowerAlarmEnable = cQx_Pending2;

	// Format the command string.
	char tTxString[100];
	if (aTxFlag)
	{
		// Cmmand to write the variable.
		sprintf(tTxString, "N%1d", tS->mTxHighPowerAlarmEnable);
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
		tS->mQxHighPowerAlarmEnable = cQx_Nak;
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
	bool tTxHighPowerAlarmEnable = tS->mTxHighPowerAlarmEnable;
	bool tRxHighPowerAlarmEnable = false;

	// 012345678901234
	// L=32768           for tx
	// 01ffclL=32768     for rx

	// If txrx.
	if (aTxFlag)
	{
		// Read from response string into temp variables.
		tRet = sscanf(tResponse, "H=%d",
			&tV);

		// Guard.
		if (tRet != 1)
		{
			Prn::print(Prn::View21, "HighPowerAlarmEnable            Nak ERROR 102 %s", tResponse);
			tS->mQxHighPowerThresh_pct = cQx_Nak;
			delete tRxString;
			return;
		}

		// Convert.
		tRxHighPowerAlarmEnable = tV & 0x8000;
		tX->mHighPowerAlarmEnable = tRxHighPowerAlarmEnable;
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
			Prn::print(Prn::View21, "HighPowerAlarmEnable            Nak ERROR 102 %s", tResponse);
			tS->mQxHighPowerThresh_pct = cQx_Nak;
			delete tRxString;
			return;
		}

		// Convert.
		tRxHighPowerAlarmEnable = tV & 0x0002;
	}

	// Compare.
	if (!aTxFlag || tTxHighPowerAlarmEnable == tRxHighPowerAlarmEnable)
	{
		// If rx only or compare ok then copy the temp to the rx variable
		// and set the qx ack code for an ack. 
		tS->mRxHighPowerAlarmEnable = tRxHighPowerAlarmEnable;
		tS->mQxHighPowerAlarmEnable = cQx_Ack;
	}
	else
	{
		// If not ok then set the qx ack code for a nak. 
		tS->mQxHighPowerAlarmEnable = cQx_Nak;
	}

	Prn::print(Prn::View21, "HighPowerAlarmEnable        %s %s",
		asString_Qx(tS->mQxHighPowerAlarmEnable), my_string_from_bool(tRxHighPowerAlarmEnable));

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