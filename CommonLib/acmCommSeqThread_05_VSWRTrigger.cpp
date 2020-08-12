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

void CommSeqThread::txrxVSWRTrigger(bool aTxFlag)
{
	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Send a command to the acm.

		// Do this first.
	ACM::SuperSettingsACM* tS = &SM::gShare->mSuperSettingsACM;
	tS->mQxVSWRTrigger = cQx_Pending2;

	// Format the command string.
	char tTxString[100];
	if (aTxFlag)
	{
		// Command to write the variable.
		sprintf(tTxString, "9%1X", tS->mTxVSWRTrigger);
	}
	else
	{
		// Command to read the variable.
		sprintf(tTxString, "8");
	}

	// Set the thread notification mask.
	mNotify.setMaskOne("CmdAck", cCmdAckNotifyCode);

	// Send the command.
	sendString(tTxString);

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
	float tTxVSWRTrigger = tS->mTxVSWRTrigger;
	float tRxVSWRTrigger = 0.0;

	// 01234567890
	// V=C

	// Guard.
	if ((tResponse[0] != 'V') ||
		(tResponse[1] != '=') ||
		(tResponse[3] != 0)
		)
	{
		Prn::print(Prn::View21, "txrxVSWRTrigger ERROR 101 %s", tResponse);
		delete tRxString;
		return;
	}

	// Read from response string into temp variables.
	tRet = sscanf(tResponse, "V=%x",
		&tV);

	// Guard.
	if (tRet != 1)
	{
		delete tRxString;
		Prn::print(Prn::View21, "txrxVSWRTrigger ERROR 102");
	}

	// Convert.
	tRxVSWRTrigger = tV;

	// If rx only then done. Copy the temp to the settings and exit.
	if (!aTxFlag)
	{
		Prn::print(Prn::View21, "VSWRTrigger %s %.2f",
			tRxVSWRTrigger);
		tS->mRxVSWRTrigger = tRxVSWRTrigger;
		delete tRxString;
		return;
	}

	// Compare the tx and rx variables.
	if (tTxVSWRTrigger == tRxVSWRTrigger)
	{
		// If ok then copy the temp to the member and set the
		// qx ack code for an ack. 
		tS->mRxVSWRTrigger = tRxVSWRTrigger;
		tS->mQxVSWRTrigger = cQx_Ack;
	}
	else
	{
		// If not ok then set the qx ack code for a nak. 
		tS->mQxVSWRTrigger = cQx_Nak;
	}

	Prn::print(Prn::View21, "VSWRTrigger %s %d",
		asString_Qx(tS->mQxVSWRTrigger), tRxVSWRTrigger);

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