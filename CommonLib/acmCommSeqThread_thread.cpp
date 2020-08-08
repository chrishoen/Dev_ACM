/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "cmnPriorities.h"
#include "cmnShare.h"
#include "acmProgramParms.h"
#define  _ACMSCRIPTSEQTHREAD_CPP_
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
   BaseClass::mShortThread->setThreadName("ScriptSeqShort");
   BaseClass::mShortThread->setThreadPriority(Cmn::gPriorities.mScriptSeqShort);
   BaseClass::mShortThread->setThreadPrintLevel(gProgramParms.mScriptSeqShortPrintLevel);

   BaseClass::mLongThread->setThreadName("ScriptSeqLong");
   BaseClass::mLongThread->setThreadPriority(Cmn::gPriorities.mScriptSeqLong);
   BaseClass::mLongThread->setThreadPrintLevel(gProgramParms.mScriptSeqLongPrintLevel);

   // Set base class call pointers.
   BaseClass::mShortThread->mThreadInitCallPointer           = std::bind(&CommSeqThread::threadInitFunction, this);
   BaseClass::mShortThread->mThreadExitCallPointer           = std::bind(&CommSeqThread::threadExitFunction, this);
   BaseClass::mShortThread->mThreadExecuteOnTimerCallPointer = std::bind(&CommSeqThread::executeOnTimer, this, _1);

   // Set qcalls.
   mTest1QCall.bind          (this->mLongThread,  this, &CommSeqThread::executeTest1);
   mTest2QCall.bind          (this->mLongThread,  this, &CommSeqThread::executeTest2);
   mRunScript1QCall.bind(this->mLongThread, this, &CommSeqThread::executeRunScript1);
   mRunScript2QCall.bind(this->mLongThread, this, &CommSeqThread::executeRunScript2);
   mAbortScriptQCall.bind    (this->mShortThread, this, &CommSeqThread::executeAbortScript);

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
void CommSeqThread::executeAbortScript()
{
   Prn::print(Prn::View01, "ABORT SCRIPT>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
   Prn::print(Prn::View01, "ABORT SCRIPT>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
   Prn::print(Prn::View01, "ABORT SCRIPT>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");

   // Abort the long thread.
   BaseClass::mNotify.abort();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Set the suspend request flag true. If the RunScript1QCall is executing
// then, when it encounters the next test script command, it saves state
// and exits in a suspended state. The script is resumed by running
// another RunScript1QCall.

void CommSeqThread::suspendScript()
{
   // Set the request flag.
   mSuspendRequestFlag = true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace