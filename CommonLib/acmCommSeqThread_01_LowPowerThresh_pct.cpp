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
   char tBuffer[200];
   float tPct = tS->mTxLowPowerThresh_pct;
   int   tN = (int)26214 * tPct / 100.0;
   if (aTxFlag)
   {
      // Write the variable.
      sprintf(tBuffer, "E%05d", tN);
   }
   else
   {
      // Read the variable.
      sprintf(tBuffer, "D");
   }

   // Test for a notification exception.
   mNotify.testException();

   // Set the thread notification mask.
   mNotify.setMaskOne("CmdAck", cCmdAckNotifyCode);

   // Send a command.
   sendString(tBuffer);

   // Wait for the acknowledgement notification.
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

	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Extract some variables from the input response string.

	// >L=32768

	// Point to the first char in the response string. 
	// If it is a '>' then advance by one char to ignore it.
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
	//
	// Guard.
	if ((tResponse[0] != 'L') ||
		(tResponse[1] != '=') ||
		(tResponse[7] != 0)
		)
	{
		Prn::print(Prn::View21, "acmSuperStateACM::updateForDE ERROR 101 %s", tResponse);
		delete tRxString;
		return;
	}

	// Read from response string into temp variables.
	tRet = sscanf(tResponse, "L=%d",
		&tV);

	// Guard.
	if (tRet != 1)
	{
		delete tRxString;
		Prn::print(Prn::View21, "acmSuperStateACM::updateForDE ERROR 102");
	}

	// Apply a mask.
	tV &= 0x7fff;

	// Convert.
	tRxLowPowerThresh_pct = 100.0 * tV / 26214.0;

	// Compare.
	if (my_closeto(tTxLowPowerThresh_pct, tRxLowPowerThresh_pct, 0.01))
	{
		// If ok then copy the temp to the member and set the
		// qx ack code for an ack. 
		tS->mRxLowPowerThresh_pct = tRxLowPowerThresh_pct;
		tS->mQxLowPowerThresh_pct = cQx_Ack;
	}
	else
	{
		// If not ok then set the qx ack code for a nak. 
		tS->mQxLowPowerThresh_pct = cQx_Nak;
	}

	Prn::print(Prn::View21, "acmSuperStateACM::updateForDE %s %.2f",
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