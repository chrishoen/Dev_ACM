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
	mTxRelayOnPowerEnable = false;
	mRxRelayOnPowerEnable = false;
	mQxRelayOnPowerEnable = 0;

	// Relay energize on VSWR alarm enable.
	mTxRelayOnVSWREnable = false;
	mRxRelayOnVSWREnable = false;
	mQxRelayOnVSWREnable = 0;

	// Check VSWR on zero power.
	mTxCheckVSWROnZeroEnable = false;
	mRxCheckVSWROnZeroEnable = false;
	mQxCheckVSWROnZeroEnable = 0;

	// PTT delay.
	mTxPTTDelay_sec = 0.0;
	mRxPTTDelay_sec = 0.0;
	mQxPTTDelay_sec = 0;

	// PTT alarm.
	mTxPTTAlarmEnable = false;
	mRxPTTAlarmEnable = false;
	mQxPTTAlarmEnable = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return true if any settings variable qx has a request or is pending.

bool SuperSettingsACM::isAnyQxRequest()
{
	return 
		mQxLowPowerThresh_pct == cQx_Request ||
		mQxLowPowerAlarmEnable == cQx_Request ||
		mQxHighPowerThresh_pct == cQx_Request ||
		mQxHighPowerAlarmEnable == cQx_Request ||
		mQxGain == cQx_Request ||
		mQxLatchAlarmEnable == cQx_Request ||
		mQxPowerUpAlarmEnable == cQx_Request ||
		mQxRelayOnPowerEnable == cQx_Request ||
		mQxRelayOnVSWREnable == cQx_Request ||
		mQxCheckVSWROnZeroEnable == cQx_Request ||
		mQxPTTDelay_sec == cQx_Request ||
		mQxPTTAlarmEnable == cQx_Request;
}
bool SuperSettingsACM::isAnyQxPending()
{
	return
		mQxLowPowerThresh_pct == cQx_Pending ||
		mQxLowPowerAlarmEnable == cQx_Pending ||
		mQxHighPowerThresh_pct == cQx_Pending ||
		mQxHighPowerAlarmEnable == cQx_Pending ||
		mQxGain == cQx_Pending ||
		mQxLatchAlarmEnable == cQx_Pending ||
		mQxPowerUpAlarmEnable == cQx_Pending ||
		mQxRelayOnPowerEnable == cQx_Pending ||
		mQxRelayOnVSWREnable == cQx_Pending ||
		mQxCheckVSWROnZeroEnable == cQx_Pending ||
		mQxPTTDelay_sec == cQx_Pending ||
		mQxPTTAlarmEnable == cQx_Pending;
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void SuperSettingsACM::show(int aPF)
{
	// Low power threshold.
	Prn::print(aPF, "LowPowerThresh_pct           %10.2f %10.2f %10s",
	   mTxLowPowerThresh_pct,
	   mRxLowPowerThresh_pct,
		asString_Qx(mQxLowPowerThresh_pct));

	// Low power alarm.
	Prn::print(aPF, "LowPowerAlarmEnable_pct      %10s %10s %10s",
		my_string_from_bool(mTxLowPowerAlarmEnable),
		my_string_from_bool(mRxLowPowerAlarmEnable),
		asString_Qx(mQxLowPowerAlarmEnable));

	// High power threshold.
	Prn::print(aPF, "HighPowerThresh_pct          %10.2f %10.2f %10s",
		mTxHighPowerThresh_pct,
		mRxHighPowerThresh_pct,
		asString_Qx(mQxHighPowerThresh_pct));

	// High power alarm.
	Prn::print(aPF, "HighPowerAlarmEnable         %10s %10s %10s",
		my_string_from_bool(mTxHighPowerAlarmEnable),
		my_string_from_bool(mRxHighPowerAlarmEnable),
	   asString_Qx(mQxHighPowerAlarmEnable));

	// Gain.
	Prn::print(aPF, "Gain                         %8d %1d %8d %1d %10s",
		mTxForwardGain,
		mTxReverseGain,
		mRxForwardGain,
		mRxReverseGain,
		asString_Qx(mQxGain));

	// Latch alarm enable.
	Prn::print(aPF, "LatchAlarmEnable             %10s %10s %10s",
		my_string_from_bool(mTxLatchAlarmEnable),
		my_string_from_bool(mRxLatchAlarmEnable),
		asString_Qx(mQxLatchAlarmEnable));

	// Power up alarm enable.
	Prn::print(aPF, "PowerUpAlarmEnable           %10s %10s %10s",
		my_string_from_bool(mTxPowerUpAlarmEnable),
		my_string_from_bool(mRxPowerUpAlarmEnable),
		asString_Qx(mQxPowerUpAlarmEnable));

	// Relay energize on power alarm enable.
	Prn::print(aPF, "RelayOnPowerAlarmEnable      %10s %10s %10s",
		my_string_from_bool(mTxRelayOnPowerEnable),
		my_string_from_bool(mRxRelayOnPowerEnable),
		asString_Qx(mQxRelayOnPowerEnable));

	// Relay energize on VSWR alarm enable.
	Prn::print(aPF, "RelayOnVSWRAlarmEnable       %10s %10s %10s",
		my_string_from_bool(mTxRelayOnVSWREnable),
		my_string_from_bool(mRxRelayOnVSWREnable),
		asString_Qx(mQxRelayOnVSWREnable));

	// Check VSWR on zero power.
	Prn::print(aPF, "CheckVSWROnZeroPowerEnable   %10s %10s %10s",
		my_string_from_bool(mTxCheckVSWROnZeroEnable),
		my_string_from_bool(mRxCheckVSWROnZeroEnable),
		asString_Qx(mQxCheckVSWROnZeroEnable));

	// PTT delay.
	Prn::print(aPF, "PTTDelay_sec                 %10.2f %10.2f %10s",
		mTxPTTDelay_sec,
		mRxPTTDelay_sec,
		asString_Qx(mQxPTTDelay_sec));

	// PTT alarm.
	// Power up alarm enable.
	Prn::print(aPF, "PTTAlarmEnable               %10s %10s %10s",
		my_string_from_bool(mTxPTTAlarmEnable),
		my_string_from_bool(mRxPTTAlarmEnable),
		asString_Qx(mQxPTTAlarmEnable));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Request the setting of settings variables. 

void SuperSettingsACM::requestLowPowerThresh_pct(float aValue)
{
	mTxLowPowerThresh_pct = aValue;
	mQxLowPowerThresh_pct = cQx_Request;
}
void SuperSettingsACM::requestLowPowerAlarmEnable(bool aValue)
{
	mTxLowPowerAlarmEnable = aValue;
	mQxLowPowerAlarmEnable = cQx_Request;
}
void SuperSettingsACM::requestHighPowerThresh_pct(float aValue)
{
	mTxHighPowerThresh_pct = aValue;
	mQxHighPowerThresh_pct = cQx_Request;
}
void SuperSettingsACM::requestHighPowerAlarmEnable(bool aValue)
{
	mTxHighPowerAlarmEnable = aValue;
	mQxHighPowerAlarmEnable = cQx_Request;
}
void SuperSettingsACM::requestGain(int aForward, int aReverse)
{
	mTxForwardGain = aForward;
	mTxReverseGain = aReverse;
	mQxGain = cQx_Request;
}
void SuperSettingsACM::requestLatchAlarmEnable(bool aValue)
{
	mTxLatchAlarmEnable = aValue;
	mQxLatchAlarmEnable = cQx_Request;
}
void SuperSettingsACM::requestPowerUpAlarmEnable(bool aValue)
{
	mTxPowerUpAlarmEnable = aValue;
	mQxPowerUpAlarmEnable = cQx_Request;
}
void SuperSettingsACM::requestRelayOnPowerEnable(bool aValue)
{
	mTxRelayOnPowerEnable = aValue;
	mQxRelayOnPowerEnable = cQx_Request;
}
void SuperSettingsACM::requestRelayOnVSWREnable(bool aValue)
{
	mTxRelayOnVSWREnable = aValue;
	mQxRelayOnVSWREnable = cQx_Request;
}
void SuperSettingsACM::requestCheckVSWROnZeroEnable(bool aValue)
{
	mTxCheckVSWROnZeroEnable = aValue;
	mQxCheckVSWROnZeroEnable = cQx_Request;
}
void SuperSettingsACM::requestPTTDelay_sec(float aValue)
{
	mTxPTTDelay_sec = aValue;
	mQxPTTDelay_sec = cQx_Request;
}
void SuperSettingsACM::requestPTTAlarmEnable(bool aValue)
{
	mTxPTTAlarmEnable = aValue;
	mQxPTTAlarmEnable = cQx_Request;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
} //namespace
