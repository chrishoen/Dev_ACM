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
// Send super settings function. This is bound to the qcall. Polls the
// super settings and for any settings variable that has pending1, send 
// a corresponding command to the acm to set the variable and then send 
// a command to read the variable as verification.

void CommSeqThread::executeSendSettings()
{
   Prn::print(Prn::View11, "CommSeqThread::executeSendSettings BEGIN");

   // Initialize the synchronization objects.
   mNotify.clearFlags();

   try
   {
      ACM::SuperSettingsACM* tS = &SM::gShare->mSuperSettingsACM;

      if (tS->mQxLowPowerThresh_pct == cQx_Pending1)
      {
         sendLowPowerThresh_pct();
      }

      if (tS->mQxLowPowerAlarmEnable == cQx_Pending1)
      {
         sendLowPowerAlarmEnable();
      }

      if (tS->mQxHighPowerThresh_pct == cQx_Pending1)
      {
         sendHighPowerThresh_pct();
      }

      if (tS->mQxHighPowerAlarmEnable == cQx_Pending1)
      {
         sendHighPowerAlarmEnable();
      }

      if (tS->mQxVSWRTrigger == cQx_Pending1)
      {
         sendVSWRTrigger();
      }

      if (tS->mQxVSWRAlarmEnable == cQx_Pending1)
      {
         sendVSWRAlarmEnable();
      }

      if (tS->mQxGain == cQx_Pending1)
      {
         sendGain();
      }

      if (tS->mQxLatchAlarmEnable == cQx_Pending1)
      {
         sendLatchAlarmEnable();
      }

      if (tS->mQxPowerUpAlarmEnable == cQx_Pending1)
      {
         sendPowerUpAlarmEnable();
      }

      if (tS->mQxRelayOnPowerEnable == cQx_Pending1)
      {
         sendRelayOnPowerEnable();
      }

      if (tS->mQxRelayOnVSWREnable == cQx_Pending1)
      {
         sendRelayOnVSWREnable();
      }

      if (tS->mQxCheckVSWROnZeroEnable == cQx_Pending1)
      {
         sendCheckVSWROnZeroEnable();
      }

      if (tS->mQxPTTDelay_sec == cQx_Pending1)
      {
         sendPTTDelay_sec();
      }

      if (tS->mQxPTTAlarmEnable == cQx_Pending1)
      {
         sendPTTAlarmEnable();
      }

   }
   catch(int aException)
   {
      Prn::print(0, "EXCEPTION CommSeqThread::executeSendSettings %d %s", aException, mNotify.mException);
   }

   // Finalize the synchronization objects.
   mAcquireWaitable.finalize();
   mNotify.clearFlags();

   Prn::print(Prn::View11, "CommSeqThread::executeSendSettings END");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Request the setting of a settings variable. 

void CommSeqThread::sendLowPowerThresh_pct()
{
   // Do this first.
   ACM::SuperSettingsACM* tS = &SM::gShare->mSuperSettingsACM;
   tS->mQxLowPowerThresh_pct = cQx_Pending2;

   // Format the command string.
   char tBuffer[200];
   float tPct = tS->mTxLowPowerThresh_pct;
   int   tN = (int)26214 * tPct / 100.0;
   sprintf(tBuffer, "E%05d", tN);

   // Test for a notification exception.
   mNotify.testException();

   // Set the thread notification mask.
   mNotify.setMaskOne("CmdAck", cCmdAckNotifyCode);

   // Send a command.
   sendString(tBuffer);

   // Wait for the acknowledgement notification.
   mNotify.wait(cCmdAckTimeout);

   // Read the receive string from the queue.
   if (std::string* tRxString = mRxStringQueue.tryRead())
   {
      // Update the settings with the receive string.
      SM::gShare->mSuperSettingsACM.updateForDE(tRxString);
      delete tRxString;
   }
   else
   {
      Prn::print(Prn::View11, "RxQueue EMPTY");
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Request the setting of a settings variable. 

void CommSeqThread::sendLowPowerAlarmEnable()
{
   // Do this first.
   ACM::SuperSettingsACM* tS = &SM::gShare->mSuperSettingsACM;
   tS->mQxLowPowerAlarmEnable = cQx_Pending2;

   // Format the command string.
   char tBuffer[200];
   float tPct = tS->mTxLowPowerThresh_pct;
   int   tN = (int)26214 * tPct / 100.0;
   sprintf(tBuffer, "G%1d", tS->mTxLowPowerAlarmEnable);

   // Test for a notification exception.
   mNotify.testException();

   // Set the thread notification mask.
   mNotify.setMaskOne("CmdAck", cCmdAckNotifyCode);

   // Send a command.
   sendString(tBuffer);

   // Wait for the acknowledgement notification.
   mNotify.wait(cCmdAckTimeout);

   // Read the receive string from the queue.
   if (std::string* tRxString = mRxStringQueue.tryRead())
   {
      // Update the settings with the receive string.
      SM::gShare->mSuperSettingsACM.updateForG(tRxString);
      delete tRxString;
   }
   else
   {
      Prn::print(Prn::View11, "RxQueue EMPTY");
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Request the setting of a settings variable. 

void CommSeqThread::sendHighPowerThresh_pct()
{
   // Do this first.
   ACM::SuperSettingsACM* tS = &SM::gShare->mSuperSettingsACM;
   tS->mQxHighPowerThresh_pct = cQx_Pending2;

   // Format the command string.
   char tBuffer[200];
   float tPct = tS->mTxHighPowerThresh_pct;
   int   tN = (int)26214 * tPct / 100.0;
   sprintf(tBuffer, "M%05d", tN);

   // Test for a notification exception.
   mNotify.testException();

   // Set the thread notification mask.
   mNotify.setMaskOne("CmdAck", cCmdAckNotifyCode);

   // Send a command.
   sendString(tBuffer);

   // Wait for the acknowledgement notification.
   mNotify.wait(cCmdAckTimeout);

   // Read the receive string from the queue.
   if (std::string* tRxString = mRxStringQueue.tryRead())
   {
      // Update the settings with the receive string.
      SM::gShare->mSuperSettingsACM.updateForLM(tRxString);
      delete tRxString;
   }
   else
   {
      Prn::print(Prn::View11, "RxQueue EMPTY");
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Request the setting of a settings variable. 

void CommSeqThread::sendHighPowerAlarmEnable()
{
   // Do this first.
   ACM::SuperSettingsACM* tS = &SM::gShare->mSuperSettingsACM;
   tS->mQxHighPowerAlarmEnable = cQx_Pending2;

   // Format the command string.
   char tBuffer[200];
   sprintf(tBuffer, "N%1d", tS->mTxHighPowerAlarmEnable);

   // Test for a notification exception.
   mNotify.testException();

   // Set the thread notification mask.
   mNotify.setMaskOne("CmdAck", cCmdAckNotifyCode);

   // Send a command.
   sendString(tBuffer);

   // Wait for the acknowledgement notification.
   mNotify.wait(cCmdAckTimeout);

   // Read the receive string from the queue.
   if (std::string* tRxString = mRxStringQueue.tryRead())
   {
      // Update the settings with the receive string.
      SM::gShare->mSuperSettingsACM.updateForN(tRxString);
      delete tRxString;
   }
   else
   {
      Prn::print(Prn::View11, "RxQueue EMPTY");
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Request the setting of a settings variable. 

void CommSeqThread::sendVSWRTrigger()
{
   // Do this first.
   ACM::SuperSettingsACM* tS = &SM::gShare->mSuperSettingsACM;
   tS->mQxVSWRTrigger = cQx_Pending2;

   // Format the command string.
   char tBuffer[200];
   sprintf(tBuffer, "9%1X", tS->mTxVSWRTrigger);

   // Test for a notification exception.
   mNotify.testException();

   // Set the thread notification mask.
   mNotify.setMaskOne("CmdAck", cCmdAckNotifyCode);

   // Send a command.
   sendString(tBuffer);

   // Wait for the acknowledgement notification.
   mNotify.wait(cCmdAckTimeout);

   // Read the receive string from the queue.
   if (std::string* tRxString = mRxStringQueue.tryRead())
   {
      // Update the settings with the receive string.
      SM::gShare->mSuperSettingsACM.updateFor89(tRxString);
      delete tRxString;
   }
   else
   {
      Prn::print(Prn::View11, "RxQueue EMPTY");
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Request the setting of a settings variable. 

void CommSeqThread::sendVSWRAlarmEnable()
{
   // Do this first.
   ACM::SuperSettingsACM* tS = &SM::gShare->mSuperSettingsACM;
   tS->mQxVSWRAlarmEnable = cQx_Pending2;

   // Format the command string.
   char tBuffer[200];
   sprintf(tBuffer, "6%1d", tS->mTxVSWRAlarmEnable);

   // Test for a notification exception.
   mNotify.testException();

   // Set the thread notification mask.
   mNotify.setMaskOne("CmdAck", cCmdAckNotifyCode);

   // Send a command.
   sendString(tBuffer);

   // Wait for the acknowledgement notification.
   mNotify.wait(cCmdAckTimeout);

   // Read the receive string from the queue.
   if (std::string* tRxString = mRxStringQueue.tryRead())
   {
      // Update the settings with the receive string.
      SM::gShare->mSuperSettingsACM.updateFor6(tRxString);
      delete tRxString;
   }
   else
   {
      Prn::print(Prn::View11, "RxQueue EMPTY");
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CommSeqThread::sendGain()
{
   // Do this first.
   ACM::SuperSettingsACM* tS = &SM::gShare->mSuperSettingsACM;
   tS->mQxGain = cQx_Pending2;
   // Format the command string.

   char tBuffer[200];
   sprintf(tBuffer, "J%1d%1d", tS->mTxForwardGain, tS->mTxReverseGain);

   // Test for a notification exception.
   mNotify.testException();

   // Set the thread notification mask.
   mNotify.setMaskOne("CmdAck", cCmdAckNotifyCode);

   // Send a command.
   sendString(tBuffer);

   // Wait for the acknowledgement notification.
   mNotify.wait(cCmdAckTimeout);

   // Read the receive string from the queue.
   if (std::string* tRxString = mRxStringQueue.tryRead())
   {
      // Update the settings with the receive string.
      SM::gShare->mSuperSettingsACM.updateForJK(tRxString);
      delete tRxString;
   }
   else
   {
      Prn::print(Prn::View11, "RxQueue EMPTY");
   }
}

void CommSeqThread::sendLatchAlarmEnable()
{
   // Do this first.
   ACM::SuperSettingsACM* tS = &SM::gShare->mSuperSettingsACM;
   tS->mQxLatchAlarmEnable = cQx_Pending2;
}
void CommSeqThread::sendPowerUpAlarmEnable()
{
   // Do this first.
   ACM::SuperSettingsACM* tS = &SM::gShare->mSuperSettingsACM;
   tS->mQxPowerUpAlarmEnable = cQx_Pending2;
}
void CommSeqThread::sendRelayOnPowerEnable()
{
   // Do this first.
   ACM::SuperSettingsACM* tS = &SM::gShare->mSuperSettingsACM;
   tS->mQxRelayOnPowerEnable = cQx_Pending2;
}
void CommSeqThread::sendRelayOnVSWREnable()
{
   // Do this first.
   ACM::SuperSettingsACM* tS = &SM::gShare->mSuperSettingsACM;
   tS->mQxRelayOnVSWREnable = cQx_Pending2;
}
void CommSeqThread::sendCheckVSWROnZeroEnable()
{
   // Do this first.
   ACM::SuperSettingsACM* tS = &SM::gShare->mSuperSettingsACM;
   tS->mQxCheckVSWROnZeroEnable = cQx_Pending2;
}
void CommSeqThread::sendPTTDelay_sec()
{
   // Do this first.
   ACM::SuperSettingsACM* tS = &SM::gShare->mSuperSettingsACM;
   tS->mQxPTTDelay_sec = cQx_Pending2;
}
void CommSeqThread::sendPTTAlarmEnable()
{
   // Do this first.
   ACM::SuperSettingsACM* tS = &SM::gShare->mSuperSettingsACM;
   tS->mQxPTTAlarmEnable = cQx_Pending2;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace