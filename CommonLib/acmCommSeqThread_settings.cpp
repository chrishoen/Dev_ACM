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
// Poll the super settings and for any settings variable that has pending1,
// send a corresponding command to the acm to set the variable and then
// process the response for verification.
//
// This can be aborted via the notification.

void CommSeqThread::doProcessSettings()
{
   Prn::print(Prn::View11, "CommSeqThread::doProcessSettings BEGIN");

   // Initialize the synchronization objects.
   mNotify.clearFlags();

   try
   {
      ACM::SuperSettingsACM* tS = &SM::gShare->mSuperSettingsACM;

      //***************************************************************************
      //***************************************************************************
      //***************************************************************************
      // Read all settings variables.

      // Do this first;
      mRxStringQueue.flushRead();

      // Test for pending requests.
      if (tS->mQxReadAllSettings == cQx_Pending1)
      {
         Prn::print(Prn::View21, "ReadAllSettings**************");
         tS->mQxReadAllSettings = cQx_Pending2;

         txrxLowPowerThresh_pct(false);
         txrxLowPowerAlarmEnable(false);
         txrxHighPowerThresh_pct(false);
         txrxHighPowerAlarmEnable(false);
         txrxVSWRTrigger(false);
         txrxVSWRAlarmEnable(false);
         txrxGain(false);
         txrxLatchAlarmEnable(false);
         txrxPowerUpAlarmEnable(false);
         txrxRelayOnAlarmEnable(false);
         txrxVSWROnZeroEnable(false);
         //txrxPTTDelay_sec(false);
         //txrxPTTAlarmEnable(false);

         tS->mQxReadAllSettings = cQx_Ack;
      }

      //***************************************************************************
      //***************************************************************************
      //***************************************************************************
      // Set individual settings variables.

      if (tS->mQxLowPowerThresh_pct == cQx_Pending1)
      {
         txrxLowPowerThresh_pct(true);
      }

      if (tS->mQxLowPowerAlarmEnable == cQx_Pending1)
      {
         txrxLowPowerAlarmEnable(true);
      }

      if (tS->mQxHighPowerThresh_pct == cQx_Pending1)
      {
         txrxHighPowerThresh_pct(true);
      }

      if (tS->mQxHighPowerAlarmEnable == cQx_Pending1)
      {
         txrxHighPowerAlarmEnable(true);
      }

      if (tS->mQxVSWRTrigger == cQx_Pending1)
      {
         txrxVSWRTrigger(true);
      }

      if (tS->mQxVSWRAlarmEnable == cQx_Pending1)
      {
         txrxVSWRAlarmEnable(true);
      }

      if (tS->mQxGain == cQx_Pending1)
      {
         txrxGain(true);
      }

      if (tS->mQxLatchAlarmEnable == cQx_Pending1)
      {
         txrxLatchAlarmEnable(true);
      }

      if (tS->mQxPowerUpAlarmEnable == cQx_Pending1)
      {
         txrxPowerUpAlarmEnable(true);
      }

      if (tS->mQxRelayOnAlarmEnable == cQx_Pending1)
      {
         txrxRelayOnAlarmEnable(true);
      }

      if (tS->mQxVSWROnZeroEnable == cQx_Pending1)
      {
         txrxVSWROnZeroEnable(true);
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
   catch (int aException)
   {
      Prn::print(0, "EXCEPTION CommSeqThread::executeSendSettings %d %s", aException, mNotify.mException);
      if (mAbortFlag) throw 1667;
   }

   // Finalize the synchronization objects.
   mNotify.clearFlags();

   Prn::print(Prn::View11, "CommSeqThread::doProcessSettings END");
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