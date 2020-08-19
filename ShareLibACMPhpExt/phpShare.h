#pragma once

/*==============================================================================
Shared memory and super state php extension library.
==============================================================================*/

#include "phpcpp.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Super state variables.

// Get all of the super state variables encoded into a json string.
Php::Value share_get_SuperStateACM_Json();

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Super settings variables.

// Get all of the super state variables encoded into a json string.
Php::Value share_get_SuperSettingsACM_Json();

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Super settings variables.

// Request the setting to read all settings. 
void share_set_SettingsReadAllSettings();

// Request the setting of settings variables. 
void share_set_SettingsLowPowerThresh_pct_float(Php::Parameters& aP);
void share_set_SettingsLowPowerAlarmEnable_bool(Php::Parameters& aP);
void share_set_SettingsHighPowerThresh_pct_float(Php::Parameters& aP);
void share_set_SettingsHighPowerAlarmEnable_bool(Php::Parameters& aP);
void share_set_SettingsVSWRTrigger_int(Php::Parameters& aP);
void share_set_SettingsVSWRAlarmEnable_bool(Php::Parameters& aP);
void share_set_SettingsGain_int_int(Php::Parameters& aP);
void share_set_SettingsLatchAlarmEnable_bool(Php::Parameters& aP);
void share_set_SettingsPowerUpAlarmEnable_bool(Php::Parameters& aP);
void share_set_SettingsRelayOnAlarmEnable_bool(Php::Parameters& aP);
void share_set_SettingsCheckVSWROnZeroEnable_bool(Php::Parameters& aP);
void share_set_SettingsPTTDelay_sec_float(Php::Parameters& aP);
void share_set_SettingsPTTAlarmEnable_bool(Php::Parameters& aP);

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Super settings variables.

// Return the setting qx status. none,request,pending1,pending2,ack,nak.
// These can be polled after making one of the above set calls.
Php::Value share_get_SettingsQxReadAllSettings();
Php::Value share_get_SettingsQxLowPowerThresh_pct();
Php::Value share_get_SettingsQxLowPowerAlarmEnable();
Php::Value share_get_SettingsQxHighPowerThresh_pct();
Php::Value share_get_SettingsQxHighPowerAlarmEnable();
Php::Value share_get_SettingsQxVSWRTrigger();
Php::Value share_get_SettingsQxVSWRAlarmEnable();
Php::Value share_get_SettingsQxGain();
Php::Value share_get_SettingsQxLatchAlarmEnable();
Php::Value share_get_SettingsQxPowerUpAlarmEnable();
Php::Value share_get_SettingsQxRelayOnAlarmEnable();
Php::Value share_get_SettingsQxCheckVSWROnZeroEnable();
Php::Value share_get_SettingsQxPTTDelay_sec();
Php::Value share_get_SettingsQxPTTAlarmEnable();

//******************************************************************************
//******************************************************************************
//******************************************************************************

