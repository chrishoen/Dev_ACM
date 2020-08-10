//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "acmSuperSettingsACM.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize.

void SuperSettingsACM::initialize()
{
	mThreshHighPower_kw = 0.0;
	mThreshHighPower_Req = false;
	mThreshHighPower_Ack = 0;

	mThreshLowPower_kw = 0.0;
	mThreshLowPower_Req = false;
	mThreshLowPower_Ack = 0;

	mThreshVSWR = 0.0;
	mThreshVSWR_Req = false;
	mThreshVSWR_Ack = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void SuperSettingsACM::show(int aPF)
{
	Prn::print(aPF, "ThreshHighPower       %10.2f %d %d",
		mThreshHighPower_kw, mThreshHighPower_Req, mThreshHighPower_Ack);
	Prn::print(aPF, "ThreshLowPower        %10.2f %d %d",
		mThreshLowPower_kw, mThreshLowPower_Req, mThreshLowPower_Ack);
	Prn::print(aPF, "ThreshVSWR            %10.2f %d %d",
		mThreshVSWR, mThreshVSWR_Req, mThreshVSWR_Ack);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.
// Request the setting of want variables. 

void SuperSettingsACM::requestThreshHighPower(float aValue)
{
	mThreshHighPower_kw = aValue;
	mThreshHighPower_Ack = 0;
	mThreshHighPower_Req = true;
}
void SuperSettingsACM::requestThreshLowPower(float aValue)
{
	mThreshLowPower_kw = aValue;
	mThreshLowPower_Ack = 0;
	mThreshLowPower_Req = true;
}
void SuperSettingsACM::requestThreshVSWR(float aValue)
{
	mThreshVSWR = aValue;
	mThreshVSWR_Ack = 0;
	mThreshVSWR_Req = true;
}
