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
// Enter a loop that periodically queries the acm for measurement
// variables. Periodically send a T command and process the response
// to calculate and set the super state variables.
//
// The loop can be aborted via the waitable or the notification.

void CommSeqThread::doProcessAcquire()
{
   Prn::print(Prn::View11, "CommSeqThread::doProcessAcquire BEGIN");

   // Initialize the synchronization objects.
   mAcquireWaitable.initialize(Cmn::gProgramParms.mDelay);
   mNotify.clearFlags();

   try
   {
      // Loop to transmit and receive.
      while (true)
      {
         // Wait for timer or abort.
         mAcquireWaitable.waitForTimerOrSemaphore();
         if (mAcquireWaitable.wasSemaphore())
         {
            // The waitable semahore as posted for an abort.
            throw 667;
         }

         // Guard.
         if (!mTPFlag) continue;

         // Test for a notification exception.
         mNotify.testException();

         // Set the thread notification mask.
         mNotify.setMaskOne("CmdAck", cCmdAckNotifyCode);

         // Send a command.
         sendString("T");

         // Wait for the acknowledgement notification.
         mNotify.wait(cCmdAckTimeout);

         // Read the receive string from the queue.
         if (std::string* tRxString = mRxStringQueue.tryRead())
         {
            SM::gShare->mSuperStateACM.updateForT(tRxString);
            delete tRxString;
         }
         else
         {
            Prn::print(Prn::View11, "RxQueue EMPTY");
         }
      }
   }
   catch(int aException)
   {
      Prn::print(0, "EXCEPTION CommSeqThread::executeAcquire %d %s", aException, mNotify.mException);
      if (mAbortFlag) throw 1667;
   }

   // Finalize the synchronization objects.
   mAcquireWaitable.finalize();
   mNotify.clearFlags();

   Prn::print(Prn::View11, "CommSeqThread::doProcessAcquire END");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace