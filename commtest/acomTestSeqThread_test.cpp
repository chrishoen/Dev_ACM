/*==============================================================================
Detestion:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "cmnShare.h"
#include "acomCommParms.h"

#include "acomTestSeqThread.h"

namespace ACom
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Run test function. This is bound to the qcall. This runs the last 
// test1 file that was generated by the file manager. It is passed a 
// resume test flag. If the flag is false then the test is new and
// the state should be reset and the test file reader should start at
// the beginning of the file. if the flag is true then the test is being
// resumed from a test suspend and the state should be restored and
// the test reader should start where it left off when the suspend
// ocurred. True means run the test file. False means resume the test
// file.
// 
// This is used for running or resuming zip test files.

void TestSeqThread::executeRunTest1(int aNumTx)
{
   Prn::print(Prn::Show4, "TestSeqThread::executeRunTest1 BEGIN");
   Prn::print(0, "running test1 %d", aNumTx);

   mLoopExitCode = cLoopExitNormal;

   if (aNumTx == -1) aNumTx = 1000*1000*1000;

   try
   {
      // Loop to transmit and receive.
      for (int i = 0; i < aNumTx; i++)
      {
         // Test for a notification exception.
         mNotify.testException();

         // Set the thread notification mask.
         mNotify.setMaskOne("CmdAck", cCmdAckNotifyCode);

         char tString[100];
         if (Ris::portableIsWindows())
         {
            sprintf(tString, "hello from windows              %d", i);
         }
         else
         {
            sprintf(tString, "hello from beagle   %d", i);
         }

         sprintf(tString, "T");

         // Send a command.
         // sendString(gCommParms.mTxCommand);
         sendString(tString);

         // Wait for the acknowledgement notification.
//       mNotify.wait(cCmdAckTimeout);

         // Loop delay.
         mNotify.waitForTimer(gCommParms.mDelay);
      }
   }
   catch(int aException)
   {
      mLoopExitCode = cLoopExitAborted;
      Prn::print(0, "EXCEPTION TestSeqThread::executeRunTest1 %d %s", aException, mNotify.mException);
   }


   // Test the exit code.
   if (mLoopExitCode == cLoopExitNormal)
   {
      // Print and log.
      Prn::print(0, "test1 done");
      Prn::print(0, "");
   }
   else if (mLoopExitCode == cLoopExitAborted)
   {
      // Print and log.
      Prn::print(0, "test1 aborted");
   }

   Prn::print(Prn::Show4, "TestSeqThread::executeRunTest1 END");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Execute test command.

void TestSeqThread::doRunCmd_Send()
{
   // Guard.
   if (!mConnectionFlag) return;

   // Set the thread notification mask.
   mNotify.setMaskOne("CmdAck", cCmdAckNotifyCode);

   // Wait for the gcode acknowledgement notification.
   mNotify.wait(cCmdAckTimeout);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace