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


void CommSeqThread::txrxLowPowerThresh_pct(bool aTxFlag)
{
//***************************************************************************
//***************************************************************************
//***************************************************************************
// Send a command to the acm.

	// Do this first.
	ACM::SuperSettingsACM* tS = &SM::gShare->mSuperSettingsACM;
	tS->mQxLowPowerThresh_pct = cQx_Pending2;

	// Format the command string.
	char tTxString[100];
	float tPct = tS->mTxLowPowerThresh_pct;
	int   tN = (int)26214 * tPct / 100.0;
	if (aTxFlag)
	{
		// Command to write the variable.
		sprintf(tTxString, "E%05d", tN);
	}
	else
	{
		// Command to read the variable.
		sprintf(tTxString, "D");
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
		tS->mQxLowPowerThresh_pct = cQx_Ack;
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
	float tTxLowPowerThresh_pct = tS->mTxLowPowerThresh_pct;
	float tRxLowPowerThresh_pct = 0.0;

	// 012345678901234
	// L=32768

	// Read from response string into temp variables.
	tRet = sscanf(tResponse, "L=%d",
		&tV);

	// Guard.
	if (tRet != 1)
	{
		Prn::print(Prn::View21, "txrxLowPowerThresh_pct Nak ERROR 102 %s", tResponse);
		tS->mQxLowPowerThresh_pct = cQx_Nak;
		delete tRxString;
		return;
	}

	// Apply a mask.
	tV &= 0x7fff;

	// Convert.
	tRxLowPowerThresh_pct = 100.0 * tV / 26214.0;

	// If rx only then done. Copy the temp to the settings and exit.
	if (!aTxFlag)
	{
		tS->mRxLowPowerThresh_pct = tRxLowPowerThresh_pct;
		tS->mQxLowPowerThresh_pct = cQx_Ack;
		Prn::print(Prn::View21, "LowPowerThresh_pct %s %.2f",
			asString_Qx(tS->mQxLowPowerThresh_pct), tRxLowPowerThresh_pct);
		delete tRxString;
		return;
	}

	// Compare the tx and rx variables.
	if (my_closeto(tTxLowPowerThresh_pct, tRxLowPowerThresh_pct, 0.01))
	{
		// If ok then copy the temp to the rx variable and set the
		// qx ack code for an ack. 
		tS->mRxLowPowerThresh_pct = tRxLowPowerThresh_pct;
		tS->mQxLowPowerThresh_pct = cQx_Ack;
	}
	else
	{
		// If not ok then set the qx ack code for a nak. 
		tS->mQxLowPowerThresh_pct = cQx_Nak;
	}

	Prn::print(Prn::View21, "LowPowerThresh_pct %s %.2f",
		asString_Qx(tS->mQxLowPowerThresh_pct), tRxLowPowerThresh_pct);

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