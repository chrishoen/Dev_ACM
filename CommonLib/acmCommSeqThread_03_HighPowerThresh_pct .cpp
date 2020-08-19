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


void CommSeqThread::txrxHighPowerThresh_pct(bool aTxFlag)
{
	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Send a command to the acm.

	// Do this first.
	ACM::SuperSettingsACM* tS = &SM::gShare->mSuperSettingsACM;
	ACM::SuperStateACM* tX = &SM::gShare->mSuperStateACM;
	tS->mQxHighPowerThresh_pct = cQx_Pending2;

	// Format the command string.
	char tTxString[100];
	float tPct = tS->mTxHighPowerThresh_pct;
	int   tN = (int)26214 * tPct / 100.0;
	if (aTxFlag)
	{
		// Command to write the variable.
		sprintf(tTxString, "M%05d", tN);
	}
	else
	{
		// Command to read the variable.
		sprintf(tTxString, "L");
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
		tS->mQxHighPowerThresh_pct = cQx_Nak;
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
	float tTxHighPowerThresh_pct = tS->mTxHighPowerThresh_pct;
	float tRxHighPowerThresh_pct = 0.0;

	// 012345678901234
	// L=32768

	// Read from response string into temp variables.
	tRet = sscanf(tResponse, "H=%d",
		&tV);

	// Guard.
	if (tRet != 1)
	{
		Prn::print(Prn::View21, "HighPowerThresh_pct             Nak ERROR 102 %s", tResponse);
		tS->mQxHighPowerThresh_pct = cQx_Nak;
		delete tRxString;
		return;
	}

	// Apply a mask.
	tV &= 0x7fff;

	// Convert.
	tRxHighPowerThresh_pct = 100.0 * tV / 26214.0;

	// Compare the tx and rx variables.
	if (!aTxFlag || my_iscloseto(tTxHighPowerThresh_pct, tRxHighPowerThresh_pct, 0.01))
	{
		// If rx only or compare ok then copy the temp to the rx variable
		// and set the qx ack code for an ack. 
		tS->mRxHighPowerThresh_pct = tRxHighPowerThresh_pct;
		tS->mQxHighPowerThresh_pct = cQx_Ack;
	}
	else
	{
		// If not ok then set the qx ack code for a nak. 
		tS->mQxHighPowerThresh_pct = cQx_Nak;
	}

	Prn::print(Prn::View21, "HighPowerThresh_pct         %s %.2f",
		asString_Qx(tS->mQxHighPowerThresh_pct), tRxHighPowerThresh_pct);

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