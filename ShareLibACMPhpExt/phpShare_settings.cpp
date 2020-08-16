/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "smShare.h"
#include "phpShare.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get shared memory super state variables as json strings.

Php::Value share_get_SuperSettingsACM_Json()
{
   return (Php::Value)SM::gShare->mSuperSettingsACM.asJsonString();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Request the setting of settings variables. 

void share_set_SettingsLowPowerThresh_pct_float(Php::Parameters& aP)
{
   SM::gShare->mSuperSettingsACM.mTxLowPowerThresh_pct = (float)(double)aP[0];
}
void share_set_SettingsLowPowerAlarmEnable_bool(Php::Parameters& aP)
{
   SM::gShare->mSuperSettingsACM.mTxLowPowerAlarmEnable = (bool)aP[0];
}
void share_set_SettingsHighPowerThresh_pct_float(Php::Parameters& aP)
{
   SM::gShare->mSuperSettingsACM.mTxHighPowerThresh_pct = (float)(double)aP[0];
}
void share_set_SettingsHighPowerAlarmEnable_bool(Php::Parameters& aP)
{
   SM::gShare->mSuperSettingsACM.mTxHighPowerAlarmEnable = (bool)aP[0];
}
void share_set_SettingsVSWRTrigger_int(Php::Parameters& aP)
{
   SM::gShare->mSuperSettingsACM.mTxVSWRTrigger = (int)aP[0];
}
void share_set_SettingsVSWRAlarmEnable_bool(Php::Parameters& aP)
{
   SM::gShare->mSuperSettingsACM.mTxVSWRAlarmEnable = (bool)aP[0];
}
void share_set_SettingsGain_int_int(Php::Parameters& aP)
{
   SM::gShare->mSuperSettingsACM.mTxForwardGain = (int)aP[0];
   SM::gShare->mSuperSettingsACM.mTxReverseGain = (int)aP[1];
}
void share_set_SettingsLatchAlarmEnable_bool(Php::Parameters& aP)
{
   SM::gShare->mSuperSettingsACM.mTxLatchAlarmEnable = (bool)aP[0];
}
void share_set_SettingsPowerUpAlarmEnable_bool(Php::Parameters& aP)
{
   SM::gShare->mSuperSettingsACM.mTxPowerUpAlarmEnable = (bool)aP[0];
}
void share_set_SettingsRelayOnPowerEnable_bool(Php::Parameters& aP)
{
   SM::gShare->mSuperSettingsACM.mTxRelayOnPowerEnable = (bool)aP[0];
}
void share_set_SettingsRelayOnVSWREnable_bool(Php::Parameters& aP)
{
   SM::gShare->mSuperSettingsACM.mTxRelayOnVSWREnable = (bool)aP[0];
}
void share_set_SettingsCheckVSWROnZeroEnable_bool(Php::Parameters& aP)
{
   SM::gShare->mSuperSettingsACM.mTxCheckVSWROnZeroEnable = (bool)aP[0];
}
void share_set_SettingsPTTDelay_sec_float(Php::Parameters& aP)
{
   SM::gShare->mSuperSettingsACM.mTxPTTDelay_sec = (float)(double)aP[0];
}
void share_set_SettingsPTTAlarmEnable_bool(Php::Parameters& aP)
{
   SM::gShare->mSuperSettingsACM.mTxPTTAlarmEnable = (bool)aP[0];
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
