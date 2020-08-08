#pragma once

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risThreadsTwoThread.h"
#include "risThreadsSynch.h"

namespace ACM
{
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a two thread that manages communications sequences with an acm.

class CommSeqThread : public Ris::Threads::BaseTwoThread
{
public:
   typedef Ris::Threads::BaseTwoThread BaseClass;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constants:

   // Lcd paint settle time.
   static const int cLcdSettleTime = 50;

   // Wait timeouts.
   static const int cGCodeAckTimeout = -1;
   static const int cLcdTimeout = 2000;

   // Notification codes.
   static const int cGCodeAckNotifyCode = 11;
   static const int cLcdNotifyCode = 12;

   static const int cFlushGCodeAckNotifyCode = 17;
   static const int cFlushLcdNotifyCode = 18;

   // Loop exit status codes.
   static const int cLoopExitNormal    = 0;
   static const int cLoopExitSuspended = 1;
   static const int cLoopExitAborted   = 2;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Notifications.
   Ris::Threads::NotifyWrapper mLcdNotify;
   Ris::Threads::NotifyWrapper mGCodeAckNotify;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Run script exit code.
   int mLoopExitCode;

   // If true then at the next test point script command that is encountered
   // in the script file the suspend exit flag is set.
   bool mSuspendRequestFlag;

   // If true then the script qcall loop exits in a suspended state.
   bool mSuspendExitFlag;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // If true the execute periodically.
   bool mTPFlag;

   // Metrics.
   int  mStatusCount1;
   int  mStatusCount2;

   // Metrics.
   int mReadCount;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   CommSeqThread();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. Thread base class overloads.

   // Thread init function. This is called by the base class immediately 
   // before the thread starts running.
   void threadInitFunction() override;

   // Thread exit function. This is called by the base class immediately 
   // after the thread starts running.
   void threadExitFunction() override;

   // Thread shutdown function. This shuts down the two threads.
   void shutdownThreads() override;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. qcalls.

   // Run script qcall. It is invoked by the command line executive.
   Ris::Threads::QCall0  mAcquireQCall;

   // Run script function. This is bound to the qcall. This executes a loop
   // that periodicall acquires data from the acm.
   void executeAcquire();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods: QCalls: These are used to send commands to the thread.

   // Abort a running qcall.

   // The qcall. This is a call that is queued to this thread.
   Ris::Threads::QCall0 mAbortQCall;

   // Execute the call in the context of this thread.
   void executeAbort();

};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance.

#ifdef _ACMCOMMSEQTHREAD_CPP_
          CommSeqThread* gCommSeqThread = 0;
#else
   extern CommSeqThread* gCommSeqThread;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
