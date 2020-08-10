//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "acmSuperDefs.h"
#include "acmSuperSettingsACM.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace ACM
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize.

void SuperSettingsACM::initialize()
{
	// Low power threshold.
	mTxLowPowerThresh_pct = 0.0;
	mRxLowPowerThresh_pct = 0.0;
	mQxLowPowerThresh_pct = 0;

	// Low power alarm.
	mTxLowPowerAlarmEnable = false;
	mRxLowPowerAlarmEnable = false;
	mQxLowPowerAlarmEnable = 0;

	// High power threshold.
	mTxHighPowerThresh_pct = 0.0;
	mRxHighPowerThresh_pct = 0.0;
	mQxHighPowerThresh_pct = 0;

	// High power alarm.
	mTxHighPowerAlarmEnable = false;
	mRxHighPowerAlarmEnable = false;
	mQxHighPowerAlarmEnable = 0;

	// Gain.
	mTxForwardGain = 0;
	mTxReverseGain = 0;
	mRxForwardGain = 0;
	mRxReverseGain = 0;
	mQxGain = 0;

	// Latch alarm enable.
	mTxLatchAlarmEnable = false;
	mRxLatchAlarmEnable = false;
	mQxLatchAlarmEnable = 0;

	// Power up alarm enable.
	mTxPowerUpAlarmEnable = false;
	mRxPowerUpAlarmEnable = false;
	mQxPowerUpAlarmEnable = 0;

	// Relay energize on power alarm enable.
	mTxRelayOnPowerAlarmEnable = false;
	mRxRelayOnPowerAlarmEnable = false;
	mQxRelayOnPowerAlarmEnable = 0;

	// Relay energize on VSWR alarm enable.
	mTxRelayOnVSWRAlarmEnable = false;
	mRxRelayOnVSWRAlarmEnable = false;
	mQxRelayOnVSWRAlarmEnable = 0;

	// Check VSWR on zero power.
	mTxCheckVSWROnZeroPower = false;
	mRxCheckVSWROnZeroPower = false;
	mQxCheckVSWROnZeroPower = 0;

	// PTT delay.
	mTxPTTDelay = 0.0;
	mRxPTTDelay = 0.0;
	mQxPTTDelay = 0;

	// PTT alarm.
	mTxPTTAlarmEnable = false;
	mRxPTTAlarmEnable = false;
	mQxPTTAlarmEnable = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void SuperSettingsACM::show(int aPF)
{
	Prn::print(aPF, "LowPowerThresh       %10.2f %10.2f %10s",
	   mTxLowPowerThresh_pct,
	   mRxLowPowerThresh_pct,
		asString_Qx(mQxLowPowerThresh_pct));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.
// Request the setting of want variables. 

void SuperSettingsACM::requestThreshHighPower(float aValue)
{
}
void SuperSettingsACM::requestThreshLowPower(float aValue)
{
}
void SuperSettingsACM::requestThreshVSWR(float aValue)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
} //namespace
