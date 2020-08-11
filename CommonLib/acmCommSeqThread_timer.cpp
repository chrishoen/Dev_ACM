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

   if (tS->mQxRelayOnPowerEnable == cQx_Request)
   {
      tS->mQxRelayOnPowerEnable = cQx_Pending1;
      tGoing = true;
   }

   if (tS->mQxRelayOnVSWREnable == cQx_Request)
   {
      tS->mQxRelayOnVSWREnable = cQx_Pending1;
      tGoing = true;
   }

   if (tS->mQxCheckVSWROnZeroEnable == cQx_Request)
   {
      tS->mQxCheckVSWROnZeroEnable = cQx_Pending1;
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

   // Send the qcall to the long thread.
   if (tGoing)
   {
      mSendSettingsQCall();
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace