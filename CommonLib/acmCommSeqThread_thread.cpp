/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "cmnPriorities.h"
#include "cmnProgramParms.h"
#define  _ACMCOMMSEQTHREAD_CPP_
#include "acmCommSeqThread.h"

namespace ACM
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

CommSeqThread::CommSeqThread()
   : mGCodeAckNotify(&mNotify, cGCodeAckNotifyCode),
     mLcdNotify(&mNotify, cLcdNotifyCode)
{
   using namespace std::placeholders;

   // Set base class thread variables.
   BaseClass::mShortThread->setThreadName("CommSeqShort");
   BaseClass::mShortThread->setThreadPriority(Cmn::gPriorities.mCommSeqShort);
   BaseClass::mShortThread->setThreadPrintLevel(Cmn::gProgramParms.mCommSeqShortPrintLevel);

   BaseClass::mLongThread->setThreadName("CommSeqLong");
   BaseClass::mLongThread->setThreadPriority(Cmn::gPriorities.mCommSeqLong);
   BaseClass::mLongThread->setThreadPrintLevel(Cmn::gProgramParms.mCommSeqLongPrintLevel);

   // Set base class call pointers.
   BaseClass::mShortThread->mThreadInitCallPointer           = std::bind(&CommSeqThread::threadInitFunction, this);
   BaseClass::mShortThread->mThreadExitCallPointer           = std::bind(&CommSeqThread::threadExitFunction, this);
   BaseClass::mShortThread->mThreadExecuteOnTimerCallPointer = std::bind(&CommSeqThread::executeOnTimer, this, _1);

   // Set qcalls.
   mAcquireQCall.bind   (this->mLongThread, this, &CommSeqThread::executeAcquire);
   mAbortQCall.bind     (this->mShortThread, this, &CommSeqThread::executeAbort);

   // Set member variables.
   mLoopExitCode = 0;
   mSuspendRequestFlag = false;
   mSuspendExitFlag = false;
   mTPFlag = false;
   mStatusCount1 = 0;
   mStatusCount2 = 0;
   mReadCount = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread init function. This is called by the base class immediately 
// before the thread starts running.

void CommSeqThread::threadInitFunction()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread exit function. This is called by the base class immediately 
// after  the thread starts running.

void CommSeqThread::threadExitFunction()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread shutdown function. This shuts down the two threads.

void CommSeqThread::shutdownThreads()
{
   // Abort the long thread.
   BaseClass::mNotify.abort();

   // Shutdown the two threads.
   BaseClass::shutdownThreads();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Abort a running grid or script qcall.
//
void CommSeqThread::executeAbort()
{
   Prn::print(Prn::View01, "ABORT>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
   Prn::print(Prn::View01, "ABORT>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
   Prn::print(Prn::View01, "ABORT>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");

   // Abort the long thread.
   BaseClass::mNotify.abort();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace