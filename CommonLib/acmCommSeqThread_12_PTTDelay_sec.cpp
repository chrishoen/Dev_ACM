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

void CommSeqThread::txrxPTTDelay_sec(bool aTxFlag)
{
	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Do this first.

	// Nicknames.
	ACM::SuperSettingsACM* tS = &SM::gShare->mSuperSettingsACM;
	ACM::SuperStateACM* tX = &SM::gShare->mSuperStateACM;
	// Pending.
	tS->mQxPTTDelay_sec = cQx_Pending2;

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
	float tRxPTTDelay_sec = 0.0;
	float tTxPTTDelay_sec = tS->mTxPTTDelay_sec;
	const char* tResponse;
	const float cConvert = 0.1566666666666666666666666;

	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Send a command to the acm.

	if (aTxFlag)
	{
		// Format the command string to write the variable.
	   tN = (int)round(tTxPTTDelay_sec / cConvert);
		sprintf(tTxString, "%%%02d", tN);
	}
	else
	{
		// Format the command string to read the variable.
		sprintf(tTxString, "#");
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
		tS->mQxPTTDelay_sec = cQx_Nak;
		delete tRxString;
		return;
	}

	// Point to the first char in the response string that is not '>'.
	tRet = 0;
	if (tRxString->c_str()[0] != '>') tResponse = &tRxString->c_str()[0];
	else                              tResponse = &tRxString->c_str()[1];

	// Read from response string into temp variables.
	tRet = sscanf(tResponse, "D=%d",
		&tV);

	// Guard.
	if (tRet != 1)
	{
		Prn::print(Prn::View21, "PTTDelay_sec                Nak ERROR 102 %s", tResponse);
		tS->mQxPTTDelay_sec = cQx_Nak;
		delete tRxString;
		return;
	}

	// Convert.
	tRxPTTDelay_sec = (float)(tV * cConvert);

	// Compare the tx and rx variables.
	if (!aTxFlag || my_iscloseto(tTxPTTDelay_sec, tRxPTTDelay_sec, 0.1))
	{
		// If rx only or compare ok then copy the temp to the rx variable
		// and set the qx ack code for an ack. 
		tS->mRxPTTDelay_sec = tRxPTTDelay_sec;
		tS->mQxPTTDelay_sec = cQx_Ack;
	}
	else
	{
		// If not ok then set the qx ack code for a nak. 
		tS->mQxPTTDelay_sec = cQx_Nak;
	}

	Prn::print(Prn::View21, "PTTDelay_sec                %s %.2f",
		asString_Qx(tS->mQxPTTDelay_sec), tRxPTTDelay_sec);

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