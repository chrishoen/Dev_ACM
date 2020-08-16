#include "stdafx.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <phpcpp.h>

#include "MainInit.h"
#include "phpShare.h"
#include "smShare.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

extern "C"
{

PHPCPP_EXPORT void * get_module()
{
	main_initialize();

	static Php::Extension ex( "ShareLibACMPhpExt", "0.1" );

	ex.add<share_get_SuperStateACM_Json>("share_get_SuperStateACM_Json");
	ex.add<share_get_SuperSettingsACM_Json>("share_get_SuperSettingsACM_Json");

	ex.add<share_set_SettingsReadAllSettings>("share_set_SettingsReadAllSettings");

	ex.add<share_set_SettingsLowPowerThresh_pct_float>("share_set_SettingsLowPowerThresh_pct_float");
	ex.add<share_set_SettingsLowPowerAlarmEnable_bool>("share_set_SettingsLowPowerAlarmEnable_bool");
	ex.add<share_set_SettingsHighPowerThresh_pct_float>("share_set_SettingsHighPowerThresh_pct_float");
	ex.add<share_set_SettingsHighPowerAlarmEnable_bool>("share_set_SettingsHighPowerAlarmEnable_bool");
	ex.add<share_set_SettingsVSWRTrigger_int>("share_set_SettingsVSWRTrigger_int");
	ex.add<share_set_SettingsVSWRAlarmEnable_bool>("share_set_SettingsVSWRAlarmEnable_bool");
	ex.add<share_set_SettingsGain_int_int>("share_set_SettingsGain_int_int");
	ex.add<share_set_SettingsLatchAlarmEnable_bool>("share_set_SettingsLatchAlarmEnable_bool");
	ex.add<share_set_SettingsPowerUpAlarmEnable_bool>("share_set_SettingsPowerUpAlarmEnable_bool");
	ex.add<share_set_SettingsRelayOnPowerEnable_bool>("share_set_SettingsRelayOnPowerEnable_bool");
	ex.add<share_set_SettingsRelayOnVSWREnable_bool>("share_set_SettingsRelayOnVSWREnable_bool");
	ex.add<share_set_SettingsCheckVSWROnZeroEnable_bool>("share_set_SettingsCheckVSWROnZeroEnable_bool");
	ex.add<share_set_SettingsPTTDelay_sec_float>("share_set_SettingsPTTDelay_sec_float");
	ex.add<share_set_SettingsPTTAlarmEnable_bool>("share_set_SettingsPTTAlarmEnable_bool");

	ex.add<share_get_SettingsQxReadAllSettings>("share_get_SettingsQxReadAllSettings");
	ex.add<share_get_SettingsQxLowPowerThresh_pct>("share_get_SettingsQxLowPowerThresh_pct");
	ex.add<share_get_SettingsQxLowPowerAlarmEnable>("share_get_SettingsQxLowPowerAlarmEnable");
	ex.add<share_get_SettingsQxHighPowerThresh_pct>("share_get_SettingsQxHighPowerThresh_pct");
	ex.add<share_get_SettingsQxHighPowerAlarmEnable>("share_get_SettingsQxHighPowerAlarmEnable");
	ex.add<share_get_SettingsQxVSWRTrigger>("share_get_SettingsQxVSWRTrigger");
	ex.add<share_get_SettingsQxVSWRAlarmEnable>("share_get_SettingsQxVSWRAlarmEnable");
	ex.add<share_get_SettingsQxGain>("share_get_SettingsQxGain");
	ex.add<share_get_SettingsQxLatchAlarmEnable>("share_get_SettingsQxLatchAlarmEnable");
	ex.add<share_get_SettingsQxPowerUpAlarmEnable>("share_get_SettingsQxPowerUpAlarmEnable");
	ex.add<share_get_SettingsQxRelayOnPowerEnable>("share_get_SettingsQxRelayOnPowerEnable");
	ex.add<share_get_SettingsQxRelayOnVSWREnable>("share_get_SettingsQxRelayOnVSWREnable");
	ex.add<share_get_SettingsQxCheckVSWROnZeroEnable>("share_get_SettingsQxCheckVSWROnZeroEnable");
	ex.add<share_get_SettingsQxPTTDelay_sec>("share_get_SettingsQxPTTDelay_sec");
	ex.add<share_get_SettingsQxPTTAlarmEnable>("share_get_SettingsQxPTTAlarmEnable");


	//******************************************************************************
	//******************************************************************************
	//******************************************************************************

	return ex;
}
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

class MyModuleInitClass
{
public:
	MyModuleInitClass()
	{
	}
	~MyModuleInitClass()
	{
		main_finalize();
	}
};

//******************************************************************************
//******************************************************************************
//******************************************************************************

MyModuleInitClass gMyModuleInitClassInstance;

//******************************************************************************
//******************************************************************************
//******************************************************************************

