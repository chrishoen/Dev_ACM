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

      //***************************************************************************
      //***************************************************************************
      //***************************************************************************
      // Read all settings variables.

      if (tS->mQxReadAllSettings == cQx_Pending1)
      {
         tS->mQxReadAllSettings = cQx_Pending2;

         txrxLowPowerThresh_pct(false);
         //txrxLowPowerAlarmEnable(false);
         //txrxHighPowerThresh_pct(false);
         //txrxHighPowerAlarmEnable(false);
         //txrxVSWRTrigger(false);
         //txrxVSWRAlarmEnable(false);
         //txrxGain(false);
         //txrxLatchAlarmEnable(false);
         //txrxPowerUpAlarmEnable(false);
         //txrxRelayOnPowerEnable(false);
         //txrxRelayOnVSWREnable(false);
         //txrxCheckVSWROnZeroEnable(false);
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