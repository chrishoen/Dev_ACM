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
void share_set_SettingsRelayOnAlarmEnable_bool(Php::Parameters& aP)
{
   SM::gShare->mSuperSettingsACM.requestRelayOnAlarmEnable((bool)aP[0]);
}
void share_set_SettingsVSWROnZeroEnable_bool(Php::Parameters& aP)
{
   SM::gShare->mSuperSettingsACM.requestVSWROnZeroEnable((bool)aP[0]);
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
// Return the setting qx status. none,request,pending1,pending2,ack,nak.
// These can be polled after making one of the above set calls.

Php::Value share_get_SettingsQxReadAllSettings()
{
   return (Php::Value)asString_Qx(SM::gShare->mSuperSettingsACM.mQxReadAllSettings);
}
Php::Value share_get_SettingsQxLowPowerThresh_pct()
{
   return (Php::Value)asString_Qx(SM::gShare->mSuperSettingsACM.mQxLowPowerThresh_pct);
}
Php::Value share_get_SettingsQxLowPowerAlarmEnable()
{
   return (Php::Value)asString_Qx(SM::gShare->mSuperSettingsACM.mQxLowPowerAlarmEnable);
}
Php::Value share_get_SettingsQxHighPowerThresh_pct()
{
   return (Php::Value)asString_Qx(SM::gShare->mSuperSettingsACM.mQxHighPowerThresh_pct);
}
Php::Value share_get_SettingsQxHighPowerAlarmEnable()
{
   return (Php::Value)asString_Qx(SM::gShare->mSuperSettingsACM.mQxHighPowerAlarmEnable);
}
Php::Value share_get_SettingsQxVSWRTrigger()
{
   return (Php::Value)asString_Qx(SM::gShare->mSuperSettingsACM.mQxVSWRTrigger);
}
Php::Value share_get_SettingsQxVSWRAlarmEnable()
{
   return (Php::Value)asString_Qx(SM::gShare->mSuperSettingsACM.mQxVSWRAlarmEnable);
}
Php::Value share_get_SettingsQxGain()
{
   return (Php::Value)asString_Qx(SM::gShare->mSuperSettingsACM.mQxGain);
}
Php::Value share_get_SettingsQxLatchAlarmEnable()
{
   return (Php::Value)asString_Qx(SM::gShare->mSuperSettingsACM.mQxLatchAlarmEnable);
}
Php::Value share_get_SettingsQxPowerUpAlarmEnable()
{
   return (Php::Value)asString_Qx(SM::gShare->mSuperSettingsACM.mQxPowerUpAlarmEnable);
}
Php::Value share_get_SettingsQxRelayOnAlarmEnable()
{
   return (Php::Value)asString_Qx(SM::gShare->mSuperSettingsACM.mQxRelayOnAlarmEnable);
}
Php::Value share_get_SettingsQxVSWROnZeroEnable()
{
   return (Php::Value)asString_Qx(SM::gShare->mSuperSettingsACM.mQxVSWROnZeroEnable);
}
Php::Value share_get_SettingsQxPTTDelay_sec()
{
   return (Php::Value)asString_Qx(SM::gShare->mSuperSettingsACM.mQxPTTDelay_sec);
}
Php::Value share_get_SettingsQxPTTAlarmEnable()
{
   return (Php::Value)asString_Qx(SM::gShare->mSuperSettingsACM.mQxPTTAlarmEnable);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
