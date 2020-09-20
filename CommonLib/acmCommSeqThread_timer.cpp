/*==============================================================================
Detestion:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "smShare.h"
#include "acmCommSeqThread.h"

namespace ACM
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread timer function.

void CommSeqThread::executeOnTimer(int aTimerCount)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // For each settings variable: check the qx code. if it is for a request
   // then set it to pending1 and send a qcall to the long thread to process
   // it.

   ACM::SuperSettingsACM* tS = &SM::gShare->mSuperSettingsACM;
   bool tGoing = false;

   // For each settings variable, set the qx code.
   if (tS->mQxReadAllSettings == cQx_Request)
   {
      tS->mQxReadAllSettings = cQx_Pending1;
      tGoing = true;
   }

   if (tS->mQxLowPowerThresh_pct == cQx_Request)
   {
      tS->mQxLowPowerThresh_pct = cQx_Pending1;
      tGoing = true;
   }

   if (tS->mQxLowPowerAlarmEnable == cQx_Request)
   {
      tS->mQxLowPowerAlarmEnable = cQx_Pending1;
      tGoing = true;
   }

   if (tS->mQxHighPowerThresh_pct == cQx_Request)
   {
      tS->mQxHighPowerThresh_pct = cQx_Pending1;
      tGoing = true;
   }

   if (tS->mQxHighPowerAlarmEnable == cQx_Request)
   {
      tS->mQxHighPowerAlarmEnable = cQx_Pending1;
      tGoing = true;
   }

   if (tS->mQxVSWRTrigger == cQx_Request)
   {
      tS->mQxVSWRTrigger = cQx_Pending1;
      tGoing = true;
   }

   if (tS->mQxVSWRAlarmEnable == cQx_Request)
   {
      tS->mQxVSWRAlarmEnable = cQx_Pending1;
      tGoing = true;
   }

   if (tS->mQxGain == cQx_Request)
   {
      tS->mQxGain = cQx_Pending1;
      tGoing = true;
   }

   if (tS->mQxLatchAlarmEnable == cQx_Request)
   {
      tS->mQxLatchAlarmEnable = cQx_Pending1;
      tGoing = true;
   }

   if (tS->mQxPowerUpAlarmEnable == cQx_Request)
   {
      tS->mQxPowerUpAlarmEnable = cQx_Pending1;
      tGoing = true;
   }

   if (tS->mQxRelayOnAlarmEnable == cQx_Request)
   {
      tS->mQxRelayOnAlarmEnable = cQx_Pending1;
      tGoing = true;
   }

   if (tS->mQxVSWROnZeroEnable == cQx_Request)
   {
      tS->mQxVSWROnZeroEnable = cQx_Pending1;
      tGoing = true;
   }

   if (tS->mQxPTTDelay_sec == cQx_Request)
   {
      tS->mQxPTTDelay_sec = cQx_Pending1;
      tGoing = true;
   }

   if (tS->mQxPTTAlarmEnable == cQx_Request)
   {
      tS->mQxPTTAlarmEnable = cQx_Pending1;
      tGoing = true;
   }

   if (tS->mQxClearAlarms == cQx_Request)
   {
      tS->mQxClearAlarms = cQx_Pending1;
      tGoing = true;
   }

   // Send the qcall to the long thread.
   if (tGoing)
   {
      // Notify the long thread.
      mAbortFlag = false;
      mSettingsFlag = true;
      mAcquireWaitable.postSemaphore();
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace