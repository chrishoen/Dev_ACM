#pragma once

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risThreadsTwoThread.h"
#include "risThreadsSynch.h"
#include "risThreadsWaitable.h"
#include "risSRSWPointerQueue.h"
#include "risSerialStringThread.h"

namespace ACM
{
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is an example master thread that sends commands to a slave thread
// and waits for responses.

class CommSeqThread : public Ris::Threads::BaseTwoThread
{
public:
   typedef Ris::Threads::BaseTwoThread BaseClass;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constants:

   // Wait timeouts.
   static const int cCmdAckTimeout = -1;

   // Notification codes.
   static const int cCmdAckNotifyCode = 11;

   static const int cFlushCmdAckNotifyCode = 17;

   // Loop exit status codes.
   static const int cLoopExitNormal    = 0;
   static const int cLoopExitAborted   = 1;

   // Timer period.
   static const int cTimerPeriod = 100;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Serial  string port child thread. It provides the thread execution
   // context for a serial string port and uses it to provide string
   // communication.
   Ris::SerialStringThread* mSerialStringThread;

   // If true then the serial port is open.
   bool mConnectionFlag;

   // If true then do some periodic processing.
   bool mTPFlag;

   // Receive string queue. Strings are received at the short thread
   // and processed in the long thread.
   Ris::SRSWPointerQueue<std::string*, 100> mRxStringQueue;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Notifications.
   Ris::Threads::NotifyWrapper mCmdAckNotify;

   // Waitable timer.
   Ris::Threads::Waitable mAcquireWaitable;

   // If true then an abort has been requested.
   bool mAbortFlag;

   // If true then a settings change has been requested.
   bool mSettingsFlag;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Run test exit code.
   int mLoopExitCode;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Metrics.
   int mTxCount;
   int mRxCount;

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

   // Thread timer function.
   void executeOnTimer(int aTimerCount) override;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. 

   // Session callback qcall.
   Ris::Threads::QCall1<bool> mSessionQCall;

   // Session qcall function. This is invoked by the child thread when 
   // the serial port is closed because of an error or when it is reopened
   // correctly.
   void executeSession(bool aConnected);

   // Receive string callback qcall.
   Ris::Threads::QCall1<std::string*> mRxStringQCall;

   // Receive string qcall function. This is invoked by the child thread 
   // when a string is received and it processes the received string
   // in the context of the short thread.
   void executeRxString(std::string* aString);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Send a null terminated string via the serial port. A newline terminator
   // is appended to the string before transmission. This executes in the
   // context of the The calling thread.
   void sendString(const char* aString);

   // Send a null terminated string via the serial port. A newline terminator
   // is appended to the string before transmission. This executes in the
   // context of the The calling thread. The string is deleted after
   // transmission.
   void sendString(std::string* aString);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods: QCalls: These are used to send commands to the thread.

   // Abort a running grid or test qcall.

   // The qcall. This is a call that is queued to this thread.
   Ris::Threads::QCall0 mAbortQCall;

   // Execute the call in the context of this thread.
   void executeAbort();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. qcalls.

   // Acquire. It is invoked by the command line executive.
   Ris::Threads::QCall0 mProcessQCall;

   // Process function. This is bound to the qcall. It runs in the context
   // of the long thread to execute a loop that periodically acquires 
   // measurement data and polls and processes settings requests.
   void executeProcess();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Enter a loop that periodically queries the acm for measurement
   // variables. Periodically send a T command and process the response
   // to calculate and set the super state variables.
   //
   // The loop can be aborted via the waitable or the notification.
   void doProcessAcquire();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Poll the super settings and for any settings variable that has pending1,
   // send a corresponding command to the acm to set the variable and then
   // process the response for verification.
   //
   // This can be aborted via the notification.
   void doProcessSettings();

   // For each individual settings variable, process the super settings
   // as follows:
   //
   // If the tx flag is true then then send a command to the acm to set the
   // variable, based on the tx variable. Receive and process the response
   // to set the rx and qx variables. 
   //
   // If the tx flag is false then send a command to the acm to read the
   // current variable. Receive and process the response to set the rx
   // variable.
   void txrxLowPowerThresh_pct(bool aTxFlag);
   void txrxLowPowerAlarmEnable(bool aTxFlag);
   void txrxHighPowerThresh_pct(bool aTxFlag);
   void txrxHighPowerAlarmEnable(bool aTxFlag);
   void txrxVSWRTrigger(bool aTxFlag);
   void txrxVSWRAlarmEnable(bool aTxFlag);
   void txrxGain(bool aTxFlag);
   void txrxLatchAlarmEnable(bool aTxFlag);
   void txrxPowerUpAlarmEnable(bool aTxFlag);
   void txrxRelayOnAlarmEnable(bool aTxFlag);
   void txrxRelayOnVSWREnable(bool aTxFlag);
   void txrxVSWROnZeroEnable(bool aTxFlag);
   void txrxPTTDelay_sec(bool aTxFlag);
   void txrxPTTAlarmEnable(bool aTxFlag);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance.

#ifdef    _ACMCOMMSEQTHREAD_CPP_
          CommSeqThread* gCommSeqThread = 0;
#else
   extern CommSeqThread* gCommSeqThread;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
