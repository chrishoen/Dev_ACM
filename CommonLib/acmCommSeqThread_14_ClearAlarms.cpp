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

void CommSeqThread::txrxClearAlarms()
{
	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Do this first.

	// Nicknames.
	ACM::SuperSettingsACM* tS = &SM::gShare->mSuperSettingsACM;
	ACM::SuperStateACM* tX = &SM::gShare->mSuperStateACM;
	// Pending.
	tS->mQxClearAlarms = cQx_Pending2;

	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Local variables.

	// Strings.
	char tTxString[100];
	std::string* tRxString = 0;
	bool tRet = false;

	// Temp variables to be extracted from the response string.
	int  tV = 0;
	int  tN = 0;
	bool tRxClearAlarms = false;
	bool tTxClearAlarms = tS->mTxClearAlarms;
	const char* tResponse;

	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Send a command to the acm.

	// Format the command string.
	sprintf(tTxString, "AQ");

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
		tS->mQxClearAlarms = cQx_Nak;
		delete tRxString;
		return;
	}

	// Point to the first char in the response string that is not '>'.
	if (tRxString->c_str()[0] != '>') tResponse = &tRxString->c_str()[0];
	else                              tResponse = &tRxString->c_str()[1];

	// Temp variables to be extracted from the response string.
	tV = 0;
	tTxClearAlarms = tS->mTxClearAlarms;
	tRxClearAlarms = false;

	// Read from response string into temp variables.
	tRet = tResponse[0] == 'A';

	// Guard.
	if (!tRet)
	{
		Prn::print(Prn::View21, "ClearAlarms               Nak ERROR 102 %s", tResponse);
		tS->mQxClearAlarms = cQx_Nak;
		delete tRxString;
		return;
	}

	// Compare.
	tRxClearAlarms = true;
   // If rx only or compare ok then copy the temp to the rx variable
	// and set the qx ack code for an ack. 
	tS->mRxClearAlarms = tRxClearAlarms;
	tS->mQxClearAlarms = cQx_Ack;

	Prn::print(Prn::View21, "ClearAlarms                 %s %s",
		asString_Qx(tS->mQxClearAlarms), my_string_from_bool(tRxClearAlarms));

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