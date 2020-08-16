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
// Request the setting to read all settings. 

void share_set_SettingsReadAllSettings()
{
   SM::gShare->mSuperSettingsACM.requestReadAllSettings();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Request the setting of settings variables. 

void share_set_SettingsLowPowerThresh_pct_float(Php::Parameters& aP)
{
   SM::gShare->mSuperSettingsACM.requestLowPowerThresh_pct((float)(double)aP[0]);
}
void share_set_SettingsLowPowerAlarmEnable_bool(Php::Parameters& aP)
{
   SM::gShare->mSuperSettingsACM.requestLowPowerAlarmEnable((bool)aP[0]);
}
void share_set_SettingsHighPowerThresh_pct_float(Php::Parameters& aP)
{
   SM::gShare->mSuperSettingsACM.requestHighPowerThresh_pct((float)(double)aP[0]);
}
void share_set_SettingsHighPowerAlarmEnable_bool(Php::Parameters& aP)
{
   SM::gShare->mSuperSettingsACM.requestHighPowerAlarmEnable((bool)aP[0]);
}
void share_set_SettingsVSWRTrigger_int(Php::Parameters& aP)
{
   SM::gShare->mSuperSettingsACM.requestVSWRTrigger((int)aP[0]);
}
void share_set_SettingsVSWRAlarmEnable_bool(Php::Parameters& aP)
{
   SM::gShare->mSuperSettingsACM.requestVSWRAlarmEnable((bool)aP[0]);
}
void share_set_SettingsGain_int_int(Php::Parameters& aP)
{
   SM::gShare->mSuperSettingsACM.requestGain((int)aP[0], (int)aP[0]);
}
void share_set_SettingsLatchAlarmEnable_bool(Php::Parameters& aP)
{
   SM::gShare->mSuperSettingsACM.requestLatchAlarmEnable((bool)aP[0]);
}
void share_set_SettingsPowerUpAlarmEnable_bool(Php::Parameters& aP)
{
   SM::gShare->mSuperSettingsACM.requestPowerUpAlarmEnable((bool)aP[0]);
}
void share_set_SettingsRelayOnPowerEnable_bool(Php::Parameters& aP)
{
   SM::gShare->mSuperSettingsACM.requestRelayOnPowerEnable((bool)aP[0]);
}
void share_set_SettingsRelayOnVSWREnable_bool(Php::Parameters& aP)
{
   SM::gShare->mSuperSettingsACM.requestRelayOnVSWREnable((bool)aP[0]);
}
void share_set_SettingsCheckVSWROnZeroEnable_bool(Php::Parameters& aP)
{
   SM::gShare->mSuperSettingsACM.requestCheckVSWROnZeroEnable((bool)aP[0]);
}
void share_set_SettingsPTTDelay_sec_float(Php::Parameters& aP)
{
   SM::gShare->mSuperSettingsACM.requestPTTDelay_sec((float)(double)aP[0]);
}
void share_set_SettingsPTTAlarmEnable_bool(Php::Parameters& aP)
{
   SM::gShare->mSuperSettingsACM.requestPTTAlarmEnable((bool)aP[0]);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
