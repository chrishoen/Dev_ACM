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
	// Do this first.

	// Nicknames.
	ACM::SuperSettingsACM* tS = &SM::gShare->mSuperSettingsACM;
	ACM::SuperStateACM* tX = &SM::gShare->mSuperStateACM;
	// Pending.
	tS->mQxVSWROnZeroEnable = cQx_Pending2;

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
	bool tRxVSWROnZeroEnable = false;
	bool tTxVSWROnZeroEnable = tS->mTxVSWROnZeroEnable;
	const char* tResponse;

	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Send a command to get the current flags.

	// Format the command string to read the current flags.
	sprintf(tTxString, "BQ");

	// Set the thread notification mask.
	mNotify.setMaskOne("CmdAck", cCmdAckNotifyCode);

	// Send the command.
	sendString(tTxString);

	// Wait for the receive response notification.
	mNotify.wait(cCmdAckTimeout);

	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Process the response from the acm for the current flags.

	// Read the receive string from the queue.
	tRxString = mRxStringQueue.tryRead();
	if (tRxString == 0)
	{
		Prn::print(Prn::View11, "RxQueue EMPTY");
		tS->mQxVSWROnZeroEnable = cQx_Nak;
		delete tRxString;
		return;
	}

	// Point to the first char in the response string that is not '>'.
	tRet = 0;
	if (tRxString->c_str()[0] != '>') tResponse = &tRxString->c_str()[0];
	else                              tResponse = &tRxString->c_str()[1];

	// Read from response string into temp variables.
	tRet = sscanf(tResponse, "%x",
		&tV);

	// Guard.
	if (tRet != 1)
	{
		Prn::print(Prn::View21, "VSWROnZeroEnable                Nak ERROR 102 %s", tResponse);
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
		// and set the qx ack code for an ack and exit. 
		tS->mRxVSWROnZeroEnable = tRxVSWROnZeroEnable;
		tS->mQxVSWROnZeroEnable = cQx_Ack;

		Prn::print(Prn::View21, "VSWROnZeroEnable            %s %s",
			asString_Qx(tS->mQxVSWROnZeroEnable), my_string_from_bool(tRxVSWROnZeroEnable));
		delete tRxString;
		return;
	}

	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Send a command to toggle the flag.

	// Format the command string to toggle the variable.
	sprintf(tTxString, "P");

	// Set the thread notification mask.
	mNotify.setMaskOne("CmdAck", cCmdAckNotifyCode);

	// Send the command.
	sendString(tTxString);

	// Wait for the receive response notification.
	mNotify.wait(cCmdAckTimeout);

	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Process the response from the acm for the toggle flag.

	// Read the receive string from the queue.
	tRxString = mRxStringQueue.tryRead();
	if (tRxString == 0)
	{
		Prn::print(Prn::View11, "RxQueue EMPTY");
		tS->mQxVSWROnZeroEnable = cQx_Nak;
		delete tRxString;
		return;
	}

	// Point to the first char in the response string that is not '>'.
	if (tRxString->c_str()[0] != '>') tResponse = &tRxString->c_str()[0];
	else                              tResponse = &tRxString->c_str()[1];

	// Temp variables to be extracted from the response string.
	tV = 0;
	tRxVSWROnZeroEnable = false;
	tTxVSWROnZeroEnable = tS->mTxVSWROnZeroEnable;

	// Read from response string into temp variables.
	tRet = sscanf(tResponse, "A=%id",
		&tV);

	// Guard.
	if (tRet != 1)
	{
		Prn::print(Prn::View21, "VSWROnZeroEnable                Nak ERROR 102 %s", tResponse);
		tS->mQxVSWROnZeroEnable = cQx_Nak;
		delete tRxString;
		return;
	}

	// Convert.
	tRxVSWROnZeroEnable = tV == 1;
	tX->mVSWROnZeroEnable = tRxVSWROnZeroEnable;

	// Compare.
	if (tTxVSWROnZeroEnable == tRxVSWROnZeroEnable)
	{
		// If rx only or compare ok then copy the temp to the rx variable
		// and set the qx ack code for an ack and exit. 
		tS->mRxVSWROnZeroEnable = tRxVSWROnZeroEnable;
		tS->mQxVSWROnZeroEnable = cQx_Ack;
	}
	else
	{
		// If not ok then set the qx ack code for a nak. 
		tS->mQxVSWROnZeroEnable = cQx_Nak;
	}

	Prn::print(Prn::View21, "VSWROnZeroEnable            %s %s",
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