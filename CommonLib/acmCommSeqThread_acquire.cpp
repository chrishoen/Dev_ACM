/*==============================================================================
Detestion:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "cmnProgramParms.h"

#include "acmCommSeqThread.h"

namespace ACM
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Acquire function. This is bound to the qcall. It runs a periodic
// acm data acquisition sequence.

void CommSeqThread::executeAcquire()
{
   Prn::print(Prn::View11, "CommSeqThread::executeAcquire BEGIN");

   mLoopExitCode = cLoopExitNormal;

   try
   {
      // Loop to transmit and receive.
      while (true)
      {
         // Test for a notification exception.
         mNotify.testException();

         // Set the thread notification mask.
         mNotify.setMaskOne("CmdAck", cCmdAckNotifyCode);

         char tString[200];
         sprintf(tString, "T");

         // Send a command.
         // sendString(Cmn::gProgramParms.mTxCommand);
         sendString(tString);

         // Wait for the acknowledgement notification.
//       mNotify.wait(cCmdAckTimeout);

         // Loop delay.
         mNotify.waitForTimer(Cmn::gProgramParms.mDelay);
      }
   }
   catch(int aException)
   {
      mLoopExitCode = cLoopExitAborted;
      Prn::print(0, "EXCEPTION CommSeqThread::executeRunTest1 %d %s", aException, mNotify.mException);
   }


   // Test the exit code.
   if (mLoopExitCode == cLoopExitNormal)
   {
      // Print and log.
      Prn::print(0, "acquire done");
      Prn::print(0, "");
   }
   else if (mLoopExitCode == cLoopExitAborted)
   {
      // Print and log.
      Prn::print(0, "acquire aborted");
   }

   Prn::print(Prn::View11, "CommSeqThread::executeAcquire END");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace