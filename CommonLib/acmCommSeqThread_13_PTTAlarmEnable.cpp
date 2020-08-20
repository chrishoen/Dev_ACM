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

void CommSeqThread::txrxPTTAlarmEnable(bool aTxFlag)
{
	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Do this first.

	// Nicknames.
	ACM::SuperSettingsACM* tS = &SM::gShare->mSuperSettingsACM;
	ACM::SuperStateACM* tX = &SM::gShare->mSuperStateACM;
	// Pending.
	tS->mQxPTTAlarmEnable = cQx_Pending2;

	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Local variables.

	// Strings.
	char tTxString[100];
	std::string* tRxString = 0;
	int tRet = 0;

	// Temp variables to be extracted from the response string.
	int  tV = 0;
	int  tN = 0;
	bool tRxPTTAlarmEnable = false;
	bool tTxPTTAlarmEnable = tS->mTxPTTAlarmEnable;
	const char* tResponse;

	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Send a command to the acm.

	// Format the command string.
	if (aTxFlag)
	{
		// Command to write the variable.
		sprintf(tTxString, "&%1dQ", tS->mTxPTTAlarmEnable);
	}
	else
	{
		// Command to read the variable.
		sprintf(tTxString, "BQ");
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
	tRxString = mRxStringQueue.tryRead();
	if (tRxString == 0)
	{
		Prn::print(Prn::View11, "RxQueue EMPTY");
		tS->mQxPTTAlarmEnable = cQx_Nak;
		delete tRxString;
		return;
	}

	// Point to the first char in the response string that is not '>'.
	if (tRxString->c_str()[0] != '>') tResponse = &tRxString->c_str()[0];
	else                              tResponse = &tRxString->c_str()[1];

	// Temp variables to be extracted from the response string.
	tV = 0;
	tTxPTTAlarmEnable = tS->mTxPTTAlarmEnable;
	tRxPTTAlarmEnable = false;

	// Read from response string into temp variables.
	tRet = sscanf(tResponse, "%x",
		&tV);

	// Guard.
	if (tRet != 1)
	{
		Prn::print(Prn::View21, "PTTAlarmEnable                  Nak ERROR 102 %s", tResponse);
		tS->mQxPTTAlarmEnable = cQx_Nak;
		delete tRxString;
		return;
	}

	// Convert.
	tX->updateFlags(tV);
	tRxPTTAlarmEnable = tX->mPTTAlarmEnable;

	// Compare.
	if (!aTxFlag || tTxPTTAlarmEnable == tRxPTTAlarmEnable)
	{
		// If rx only or compare ok then copy the temp to the rx variable
		// and set the qx ack code for an ack. 
		tS->mRxPTTAlarmEnable = tRxPTTAlarmEnable;
		tS->mQxPTTAlarmEnable = cQx_Ack;
	}
	else
	{
		// If not ok then set the qx ack code for a nak. 
		tS->mQxPTTAlarmEnable = cQx_Nak;
	}

	Prn::print(Prn::View21, "PTTAlarmEnable              %s %s",
		asString_Qx(tS->mQxPTTAlarmEnable), my_string_from_bool(tRxPTTAlarmEnable));

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