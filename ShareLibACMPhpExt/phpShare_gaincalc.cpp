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
// Set shared memory gain calculation variables.

void share_set_GainCalc_AttenSetting_Float(Php::Parameters& aP)
{
   Prn::print(Prn::View31, "share_set_GainCalc_AttenSetting_Float %4.2f", aP[0].floatValue());
   SM::gShare->mGainCalc.mAttenSetting = aP[0].floatValue();
}
void share_set_GainCalc_AntJumperLoss_Float(Php::Parameters& aP)
{
   Prn::print(Prn::View31, "share_set_GainCalc_AntJumperLoss_Float %4.2f", aP[0].floatValue());
   SM::gShare->mGainCalc.mAntJumperLoss = aP[0].floatValue();
}
void share_set_GainCalc_AntFeedlineLoss_Float(Php::Parameters& aP)
{
   Prn::print(Prn::View31, "share_set_GainCalc_AntFeedlineLoss_Float %4.2f", aP[0].floatValue());
   SM::gShare->mGainCalc.mAntFeedlineLoss = aP[0].floatValue();
}
void share_set_GainCalc_SurgeProtLoss_Float(Php::Parameters& aP)
{
   Prn::print(Prn::View31, "share_set_GainCalc_SurgeProtLoss_Float %4.2f", aP[0].floatValue());
   SM::gShare->mGainCalc.mSurgeProtLoss = aP[0].floatValue();
}
void share_set_GainCalc_InsideJumperLoss_Float(Php::Parameters& aP)
{
   Prn::print(Prn::View31, "share_set_GainCalc_InsideJumperLoss_Float %4.2f", aP[0].floatValue());
   SM::gShare->mGainCalc.mInsideJumperLoss = aP[0].floatValue();
}
void share_set_GainCalc_RxJumperLoss_Float(Php::Parameters& aP)
{
   Prn::print(Prn::View31, "share_set_GainCalc_RxJumperLoss_Float %4.2f", aP[0].floatValue());
   SM::gShare->mGainCalc.mRxJumperLoss = aP[0].floatValue();
}
void share_set_GainCalc_RMCGain_Float(Php::Parameters& aP)
{
   Prn::print(Prn::View31, "share_set_GainCalc_RMCGain_Float %4.2f", aP[0].floatValue());
   SM::gShare->mGainCalc.mRMCGain = aP[0].floatValue();
}
void share_set_GainCalc_DesiredRxGain_Float(Php::Parameters& aP)
{
   Prn::print(Prn::View31, "share_set_GainCalc_DesiredRxGain_Float %4.2f", aP[0].floatValue());
   SM::gShare->mGainCalc.mDesiredRxGain = aP[0].floatValue();
}

void share_set_GainCalc_TestportFeedlineLoss_Float(Php::Parameters& aP)
{
   Prn::print(Prn::View31, "share_set_GainCalc_TestportFeedlineLoss_Float %4.2f", aP[0].floatValue());
   SM::gShare->mGainCalc.mTestportFeedlineLoss = aP[0].floatValue();
}
void share_set_GainCalc_TestportSurgeProtLoss_Float(Php::Parameters& aP)
{
   Prn::print(Prn::View31, "share_set_GainCalc_TestportSurgeProtLoss_Float %4.2f", aP[0].floatValue());
   SM::gShare->mGainCalc.mTestportSurgeProtLoss = aP[0].floatValue();
}
void share_set_GainCalc_TestportJumperLoss_Float(Php::Parameters& aP)
{
   Prn::print(Prn::View31, "share_set_GainCalc_TestportJumperLoss_Float %4.2f", aP[0].floatValue());
   SM::gShare->mGainCalc.mTestportJumperLoss = aP[0].floatValue();
}
void share_set_GainCalc_TestCable4Loss_Float(Php::Parameters& aP)
{
   Prn::print(Prn::View31, "share_set_GainCalc_TestCable4Loss_Float %4.2f", aP[0].floatValue());
   SM::gShare->mGainCalc.mTestCable4Loss = aP[0].floatValue();
}
void share_set_GainCalc_RSSILevel_Float(Php::Parameters& aP)
{
   Prn::print(Prn::View31, "share_set_GainCalc_RSSILevel_Float %4.2f", aP[0].floatValue());
   SM::gShare->mGainCalc.mRSSILevel = aP[0].floatValue();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get all of the super state variables encoded into a json string.

Php::Value share_get_GainCalc_Json()
{
   Prn::print(Prn::View31, "share_get_GainCalc_Json");
   return (Php::Value)SM::gShare->mGainCalc.getJsonString();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Perform gain calculation operations.

void share_do_GainCalc_ReadModifyWriteBegin()
{
   Prn::print(Prn::View31, "share_do_GainCalc_ReadModifyWriteBegin");
   SM::gShare->mGainCalc.doReadModifyWriteBegin();
}
void share_do_GainCalc_ReadModifyWriteEnd()
{
   Prn::print(Prn::View31, "share_do_GainCalc_ReadModifyWriteEnd");
   SM::gShare->mGainCalc.doReadModifyWriteEnd();
}
void share_do_GainCalc_ProtectedRead()
{
   Prn::print(Prn::View31, "share_do_GainCalc_ProtectedRead");
   SM::gShare->mGainCalc.doProtectedRead();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
