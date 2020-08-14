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

		ex.add<share_set_X1_Int>("share_set_X1_Int");
		ex.add<share_set_X2_Int>("share_set_X2_Int");
		ex.add<share_set_X3_Int>("share_set_X3_Int");
		ex.add<share_set_X4_Int>("share_set_X4_Int");

		ex.add<share_get_X1_Int>("share_get_X1_Int");
		ex.add<share_get_X2_Int>("share_get_X2_Int");
		ex.add<share_get_X3_Int>("share_get_X3_Int");
		ex.add<share_get_X4_Int>("share_get_X4_Int");

		ex.add<share_set_SuperStateBoth_TestMode_None>("share_set_SuperStateBoth_TestMode_None");
		ex.add<share_set_SuperStateBoth_TestMode_TerminateA>("share_set_SuperStateBoth_TestMode_TerminateA");
		ex.add<share_set_SuperStateBoth_TestMode_TerminateB>("share_set_SuperStateBoth_TestMode_TerminateB");
		ex.add<share_set_SuperStateBoth_TestMode_AntSweep>("share_set_SuperStateBoth_TestMode_AntSweep");
		ex.add<share_set_SuperStateBoth_TestMode_BypassDA>("share_set_SuperStateBoth_TestMode_BypassDA");
		ex.add<share_set_SuperStateBoth_TestMode_BypassTTA>("share_set_SuperStateBoth_TestMode_BypassTTA");
		ex.add<share_set_SuperStateBoth_TestMode_BypassBoth>("share_set_SuperStateBoth_TestMode_BypassBoth");
		ex.add<share_set_SuperStateDA_UserAtten_Float>("share_set_SuperStateDA_UserAtten_Float");
		ex.add<share_set_SuperStateTTA_PreferRFPath_AB>("share_set_SuperStateTTA_PreferRFPath_AB");
		ex.add<share_set_SuperStateTTA_Aux12VEnable_Bool>("share_set_SuperStateTTA_Aux12VEnable_Bool");

		ex.add<share_get_SuperStateTTA_Json>("share_get_SuperStateTTA_Json");
		ex.add<share_get_SuperStateDA_Json>("share_get_SuperStateDA_Json");
		ex.add<share_get_SuperStateCU_Json>("share_get_SuperStateCU_Json");
		ex.add<share_get_ModeInfo_Json>("share_get_ModeInfo_Json");

		ex.add<share_set_GainCalc_AttenSetting_Float>("share_set_GainCalc_AttenSetting_Float");
		ex.add<share_set_GainCalc_AntJumperLoss_Float>("share_set_GainCalc_AntJumperLoss_Float");
		ex.add<share_set_GainCalc_AntFeedlineLoss_Float>("share_set_GainCalc_AntFeedlineLoss_Float");
		ex.add<share_set_GainCalc_SurgeProtLoss_Float>("share_set_GainCalc_SurgeProtLoss_Float");
		ex.add<share_set_GainCalc_InsideJumperLoss_Float>("share_set_GainCalc_InsideJumperLoss_Float");
		ex.add<share_set_GainCalc_RxJumperLoss_Float>("share_set_GainCalc_RxJumperLoss_Float");
		ex.add<share_set_GainCalc_RMCGain_Float>("share_set_GainCalc_RMCGain_Float");
   	ex.add<share_set_GainCalc_DesiredRxGain_Float>("share_set_GainCalc_DesiredRxGain_Float");

		ex.add<share_set_GainCalc_TestportFeedlineLoss_Float>("share_set_GainCalc_TestportFeedlineLoss_Float");
		ex.add<share_set_GainCalc_TestportSurgeProtLoss_Float>("share_set_GainCalc_TestportSurgeProtLoss_Float");
		ex.add<share_set_GainCalc_TestportJumperLoss_Float>("share_set_GainCalc_TestportJumperLoss_Float");
		ex.add<share_set_GainCalc_TestCable4Loss_Float>("share_set_GainCalc_TestCable4Loss_Float");
		ex.add<share_set_GainCalc_RSSILevel_Float>("share_set_GainCalc_RSSILevel_Float");

		ex.add<share_do_GainCalc_ReadModifyWriteBegin>("share_do_GainCalc_ReadModifyWriteBegin");
   	ex.add<share_do_GainCalc_ReadModifyWriteEnd>("share_do_GainCalc_ReadModifyWriteEnd");
		ex.add<share_do_GainCalc_ProtectedRead>("share_do_GainCalc_ProtectedRead");
		ex.add<share_get_GainCalc_Json>("share_get_GainCalc_Json");

		ex.add<share_set_AuxAlarmMode_Low_Int>("share_set_AuxAlarmMode_Low_Int");
		ex.add<share_set_AuxAlarmMode_High_Int>("share_set_AuxAlarmMode_High_Int");
		ex.add<share_set_AuxAlarmMode_Test_Int>("share_set_AuxAlarmMode_Test_Int");
		ex.add<share_set_AuxAlarmEnable_Int_Bool>("share_set_AuxAlarmEnable_Int_Bool");
		ex.add<share_get_AuxAlarmMode_Json>("share_get_AuxAlarmMode_Json");
		
		ex.add<share_get_SysInfo_Json>("share_get_SysInfo_Json");

		ex.add<share_get_SystemTime>("share_get_SystemTime");

		ex.add<share_tryEventNotifyQueueRead>("share_tryEventNotifyQueueRead");
		ex.add<share_finishEventNotifyQueueRead>("share_finishEventNotifyQueueRead");

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

