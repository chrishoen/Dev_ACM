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

   // Initialize the synchronization objects.
   mAcquireWaitable.initialize(2000);
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

         // Test for a notification exception.
         mNotify.testException();

         // Set the thread notification mask.
         mNotify.setMaskOne("CmdAck", cCmdAckNotifyCode);

         // Send a command.
         sendString("T");

         // Wait for the acknowledgement notification.
         mNotify.wait(cCmdAckTimeout);

         // Read the receive string from the queue.
         std::string* tRxString;
         if (mRxStringQueue.tryRead(&tRxString))
         {
            Prn::print(Prn::View11, "RxQueue %s", tRxString->c_str());
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
   }

   Prn::print(Prn::View11, "CommSeqThread::executeAcquire END");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace