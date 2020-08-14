/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "smShare.h"
#include "SysInfo.h"
#include "phpShare.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Set auxiliary alarm modes, user input 1..5.

void share_set_AuxAlarmMode_Low_Int(Php::Parameters& aP)
{
   SM::gShare->setAuxAlarmMode_Low((int)aP[0].numericValue());
}
void share_set_AuxAlarmMode_High_Int(Php::Parameters& aP)
{
   SM::gShare->setAuxAlarmMode_High((int)aP[0].numericValue());
}
void share_set_AuxAlarmMode_Test_Int(Php::Parameters& aP)
{
   SM::gShare->setAuxAlarmMode_Test((int)aP[0].numericValue());
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Set auxiliary alarm enables, user input 1..5. , bool enable

void share_set_AuxAlarmEnable_Int_Bool(Php::Parameters& aP)
{
   SM::gShare->setAuxAlarmEnable((int)aP[0].numericValue(),aP[1].boolValue());
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get all of the variables encoded into a json string.

Php::Value share_get_AuxAlarmMode_Json()
{
   Prn::print(Prn::View31, "share_get_AuxAlarmMode_Json");
   return (Php::Value)SM::gShare->mAuxAlarmMode.getJsonString();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get all of the variables encoded into a json string.

Php::Value share_get_SysInfo_Json()
{
   Prn::print(Prn::View31, "share_get_SysInfo_Json");
   gSysInfo.doProtectedRead();
   return (Php::Value)gSysInfo.getJsonString();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
