/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "SuperStateExtraTTA.h"
#include "SuperStateExtraDA.h"
#include "smShare.h"
#include "phpShare.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get shared memory super state variables as json strings.

Php::Value share_get_SuperStateTTA_Json()
{
   return (Php::Value)SuperStateTTA_asJsonString(&SM::gShare->mSuperStateTTA);
}

Php::Value share_get_SuperStateDA_Json()
{
   return (Php::Value)SuperStateDA_asJsonString(&SM::gShare->mSuperStateDA);
}

Php::Value share_get_SuperStateCU_Json()
{
   return (Php::Value)SM::gShare->mSuperStateCU.getJsonString();
}

// Get the mode info.
Php::Value share_get_ModeInfo_Json()
{
   return (Php::Value)SM::gShare->mModeInfo.getJsonString();
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Set the test mode for da and tta.

void share_set_SuperStateBoth_TestMode_None()
{
   SM::gShare->setTestMode_None();
}
void share_set_SuperStateBoth_TestMode_TerminateA(Php::Parameters& aP)
{
   SM::gShare->setTestMode_TerminateA((int)aP[0]);
}
void share_set_SuperStateBoth_TestMode_TerminateB(Php::Parameters& aP)
{
   SM::gShare->setTestMode_TerminateB((int)aP[0]);
}
void share_set_SuperStateBoth_TestMode_AntSweep(Php::Parameters& aP)
{
   SM::gShare->setTestMode_AntSweep((int)aP[0]);
}
void share_set_SuperStateBoth_TestMode_BypassDA(Php::Parameters& aP)
{
   SM::gShare->setTestMode_BypassDA((int)aP[0]);
}
void share_set_SuperStateBoth_TestMode_BypassTTA(Php::Parameters& aP)
{
   SM::gShare->setTestMode_BypassTTA((int)aP[0]);
}
void share_set_SuperStateBoth_TestMode_BypassBoth(Php::Parameters& aP)
{
   SM::gShare->setTestMode_BypassBoth((int)aP[0]);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Set da want variables.

void share_set_SuperStateDA_UserAtten_Float(Php::Parameters& aP)
{
   SM::gShare->setDA_UserAtten(aP[0].floatValue());
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// set tta want variables.

void share_set_SuperStateTTA_PreferRFPath_AB(Php::Parameters& aP)
{
   if (aP[0] == "A" || aP[0] == "a")
   {
      SM::gShare->setTTA_PreferRFPath(0);
   }
   else
   {
      SM::gShare->setTTA_PreferRFPath(1);
   }
}

void share_set_SuperStateTTA_Aux12VEnable_Bool(Php::Parameters& aP)
{
   SM::gShare->setTTA_Aux12VEnable(aP[0].boolValue());
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
