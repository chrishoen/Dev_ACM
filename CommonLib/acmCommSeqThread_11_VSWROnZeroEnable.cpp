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

void CommSeqThread::txrxVSWROnZeroEnable(bool aTxFlag)
{
	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Send a command to the acm.

	// Do this first.
	ACM::SuperSettingsACM* tS = &SM::gShare->mSuperSettingsACM;
	ACM::SuperStateACM* tX = &SM::gShare->mSuperStateACM;
	tS->mQxVSWROnZeroEnable = cQx_Pending2;

	// Format the command string.
	char tTxString[100];
	if (aTxFlag)
	{
		// Command to write the variable.
		sprintf(tTxString, "5%1dQ", tS->mTxVSWROnZeroEnable);
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
	std::string* tRxString = mRxStringQueue.tryRead();
	if (tRxString == 0)
	{
		Prn::print(Prn::View11, "RxQueue EMPTY");
		tS->mQxVSWROnZeroEnable = cQx_Nak;
		delete tRxString;
		return;
	}

	// Point to the first char in the response string that is not '>'.
	int tRet = 0;
	const char* tResponse;
	if (tRxString->c_str()[0] != '>') tResponse = &tRxString->c_str()[0];
	else                              tResponse = &tRxString->c_str()[1];

	// Temp variables to be extracted from the response string.
	int   tV = 0;
	bool tRxVSWROnZeroEnable = false;
	bool tTxVSWROnZeroEnable = tS->mTxVSWROnZeroEnable;

	// 012345678901234
	// 0024clL=32768

	// Read from response string into temp variables.
	tRet = sscanf(tResponse, "%x",
		&tV);

	// Guard.
	if (tRet != 1)
	{
		Prn::print(Prn::View21, "VSWROnZeroEnable              Nak ERROR 102 %s", tResponse);
		tS->mQxVSWROnZeroEnable = cQx_Nak;
		delete tRxString;
		return;
	}

	// Convert.
	tX->updateFlags(tV);
	tRxVSWROnZeroEnable = tX->mVSWROnZeroEnable;

	// Compare.
	if (!aTxFlag || tTxVSWROnZeroEnable == tRxVSWROnZeroEnable)
	{
		// If rx only or compare ok then copy the temp to the rx variable
		// and set the qx ack code for an ack. 
		tS->mRxVSWROnZeroEnable = tRxVSWROnZeroEnable;
		tS->mQxVSWROnZeroEnable = cQx_Ack;
	}
	else
	{
		// If not ok then set the qx ack code for a nak. 
		tS->mQxVSWROnZeroEnable = cQx_Nak;
	}

	Prn::print(Prn::View21, "VSWROnZeroEnable          %s %s",
		asString_Qx(tS->mQxVSWROnZeroEnable), my_string_from_bool(tRxVSWROnZeroEnable));

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