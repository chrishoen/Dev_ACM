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

void CommSeqThread::txrxGain(bool aTxFlag)
{
	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Send a command to the acm.

		// Do this first.
	ACM::SuperSettingsACM* tS = &SM::gShare->mSuperSettingsACM;
	tS->mQxGain = cQx_Pending2;

	// Format the command string.
	char tTxString[100];
	if (aTxFlag)
	{
		// Command to write the variable.
		sprintf(tTxString, "J%1d%1d", tS->mTxForwardGain, tS->mTxReverseGain);
	}
	else
	{
		// Command to read the variable.
		sprintf(tTxString, "K");
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
		tS->mQxLowPowerThresh_pct = cQx_Nak;
		delete tRxString;
		return;
	}

	// Point to the first char in the response string that is not '>'.
	int tRet = 0;
	const char* tResponse;
	if (tRxString->c_str()[0] != '>') tResponse = &tRxString->c_str()[0];
	else                              tResponse = &tRxString->c_str()[1];

	// Temp variables to be extracted from the response string.
	int tV1 = -1;
	int tV2 = -1;
	int tTxForwardGain = tS->mTxForwardGain;
	int tTxReverseGain = tS->mTxReverseGain;
	int tRxForwardGain = 0;
	int tRxReverseGain = 0;

	// 01234567JK01234
	// G=88
	// E

	// If an error code was received then exit.
	if (strcmp(tResponse, "E") == 0)
	{
		Prn::print(Prn::View21, "Gain                        Nak ERROR 101 %s", tResponse);
		tS->mQxGain = cQx_Nak;
		delete tRxString;
		return;
	}

	// Read from response string into temp variables.
	tRet = sscanf(tResponse, "G=%1d%1d",
		&tV1, &tV2);

	// Guard.
	if (tRet != 2)
	{
		Prn::print(Prn::View21, "Gain                            Nak ERROR 102 %s", tResponse);
		tS->mQxLowPowerThresh_pct = cQx_Nak;
		delete tRxString;
		return;
	}

	// Convert.
	tRxForwardGain = tV1;
	tRxReverseGain = tV2;

	// Compare the tx and rx variables.
	if (!aTxFlag || tRxForwardGain == tTxForwardGain && tRxReverseGain == tTxReverseGain)
	{
		// If rx only or compare ok then copy the temp to the rx variable
		// and set the qx ack code for an ack. 
		tS->mRxForwardGain = tRxForwardGain;
		tS->mRxReverseGain = tRxReverseGain;
		tS->mQxGain = cQx_Ack;
	}
	else
	{
		// If not ok then set the qx ack code for a nak. 
		tS->mQxGain = cQx_Nak;
	}

	Prn::print(Prn::View21, "Gain                        %s %d  %d",
		asString_Qx(tS->mQxGain), tRxForwardGain, tRxReverseGain);

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