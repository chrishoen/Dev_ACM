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
	// Low power threshold.
	Prn::print(aPF, "LowPowerThresh          %10.2f %10.2f %10s",
	   mTxLowPowerThresh_pct,
	   mRxLowPowerThresh_pct,
		asString_Qx(mQxLowPowerThresh_pct));

	// Low power alarm.
	Prn::print(aPF, "LowPowerAlarmEnable     %10s %10s %10s",
		my_string_from_bool(mTxLowPowerAlarmEnable),
		my_string_from_bool(mRxLowPowerAlarmEnable),
		asString_Qx(mQxLowPowerAlarmEnable));

	// High power threshold.
	Prn::print(aPF, "HighPowerThresh         %10.2f %10.2f %10s",
		mTxHighPowerThresh_pct,
		mRxHighPowerThresh_pct,
		asString_Qx(mQxHighPowerThresh_pct));

	// High power alarm.
	Prn::print(aPF, "HighPowerAlarmEnable    %10s %10s %10s",
		my_string_from_bool(mTxHighPowerAlarmEnable),
		my_string_from_bool(mRxHighPowerAlarmEnable),
	   asString_Qx(mQxHighPowerAlarmEnable));

	// Gain.
	Prn::print(aPF, "Gain                    %8d %1d %8d %1d %10s",
		mTxForwardGain,
		mTxReverseGain,
		mRxForwardGain,
		mRxReverseGain,
		asString_Qx(mQxGain));
	return;

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
// Request the setting of want variables. 

void SuperSettingsACM::requestThreshLowPower(float aValue)
{
}
void SuperSettingsACM::requestThreshHighPower(float aValue)
{
}
void SuperSettingsACM::requestThreshVSWR(float aValue)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
} //namespace
