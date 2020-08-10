/*==============================================================================
Detestion:
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
   : mCmdAckNotify(&mNotify, cCmdAckNotifyCode)
{
   using namespace std::placeholders;

   // Set base class thread variables.
   BaseClass::mShortThread->setThreadName("CommSeqShort");
   BaseClass::mShortThread->setThreadPriority(Cmn::gPriorities.mCommSeqShort);
   BaseClass::mShortThread->setThreadPrintLevel(Cmn::gProgramParms.mCommSeqShortPrintLevel);
   BaseClass::mShortThread->mTimerPeriod = cTimerPeriod;

   BaseClass::mLongThread->setThreadName("CommSeqLong");
   BaseClass::mLongThread->setThreadPriority(Cmn::gPriorities.mCommSeqLong);
   BaseClass::mLongThread->setThreadPrintLevel(Cmn::gProgramParms.mCommSeqLongPrintLevel);

   // Set base class call pointers.
   BaseClass::mShortThread->mThreadInitCallPointer           = std::bind(&CommSeqThread::threadInitFunction, this);
   BaseClass::mShortThread->mThreadExitCallPointer           = std::bind(&CommSeqThread::threadExitFunction, this);
   BaseClass::mShortThread->mThreadExecuteOnTimerCallPointer = std::bind(&CommSeqThread::executeOnTimer, this, _1);

   // Set qcalls.
   mSessionQCall.bind       (this->mShortThread, this, &CommSeqThread::executeSession);
   mRxStringQCall.bind      (this->mShortThread, this, &CommSeqThread::executeRxString);
   mAcquireQCall.bind       (this->mLongThread, this, &CommSeqThread::executeAcquire);
   mAbortQCall.bind         (this->mShortThread, this, &CommSeqThread::executeAbort);
   mSendSettingsQCall.bind  (this->mLongThread, this, &CommSeqThread::executeSendSettings);

   // Set member variables.
   mLoopExitCode = 0;
   mTxCount = 0;
   mRxCount = 0;

   mRxStringQueue.reset();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread init function. This is called by the base class immediately 
// before the thread starts running.

void CommSeqThread::threadInitFunction()
{
   using namespace std::placeholders;

   // Instance of serial port settings.
   Ris::SerialSettings tSerialSettings;

   tSerialSettings.setPortDevice(Cmn::gProgramParms.mCmdCommPortDevice);
   tSerialSettings.setPortSetup(Cmn::gProgramParms.mCmdCommPortSetup);
   tSerialSettings.mRxTimeout = Cmn::gProgramParms.mCmdCommPortTimeout;
   tSerialSettings.mTermMode = Ris::cSerialTermMode_CRLF;
   tSerialSettings.mThreadPriority = Cmn::gPriorities.mSerialString;
   tSerialSettings.mPrintLevel = Cmn::gProgramParms.mSerialStringPrintLevel;
   tSerialSettings.mSessionQCall = mSessionQCall;
   tSerialSettings.mRxStringQCall = mRxStringQCall;
   tSerialSettings.m485Flag = Cmn::gProgramParms.mCmdCommPort485Flag;

   // Create the child thread.
   mSerialStringThread = new Ris::SerialStringThread(tSerialSettings);

   // Launch the child thread.
   mSerialStringThread->launchThread();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread exit function. This is called by the base class immediately 
// after  the thread starts running.

void CommSeqThread::threadExitFunction()
{
   // Shutdown the child thread
   mSerialStringThread->shutdownThread();
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
// Abort a running grid or test qcall.
//
void CommSeqThread::executeAbort()
{
   Prn::print(Prn::View11, "ABORT>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");

   // Abort the long thread.
   BaseClass::mNotify.abort();
   mAcquireWaitable.postSemaphore();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Session qcall function. This is invoked by the child thread when 
// the serial port is closed because of an error or when it is reopened
// correctly.

void CommSeqThread::executeSession(bool aConnected)
{
   if (aConnected)
   {
      Prn::print(0, "CommSeqThread serial port open  CONNECTED");
   }
   else
   {
      Prn::print(0, "CommSeqThread serial port error DISCONNECTED");
   }

   mConnectionFlag = aConnected;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace