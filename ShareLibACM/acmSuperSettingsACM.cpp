//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "json.h"
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
	// Read all settings.
	mQxReadAllSettings = 0;

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

	// VSWR trigger.
	mTxVSWRTrigger = 0;
	mRxVSWRTrigger = 0;
	mQxVSWRTrigger = 0;

	// VSWR alarm.
	mTxVSWRAlarmEnable = false;
	mRxVSWRAlarmEnable = false;
	mQxVSWRAlarmEnable = 0;

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

	// Relay energize on alarm enable.
	mTxRelayOnAlarmEnable = false;
	mRxRelayOnAlarmEnable = false;
	mQxRelayOnAlarmEnable = 0;

	// VSWR on zero power.
	mTxVSWROnZeroEnable = false;
	mRxVSWROnZeroEnable = false;
	mQxVSWROnZeroEnable = 0;

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
// Show.

void SuperSettingsACM::show(int aPF)
{
	// Read all settings.
	Prn::print(aPF, "ReadAllSettings              %10s",
		asString_Qx(mQxReadAllSettings));

	// Low power threshold.
	Prn::print(aPF, "LowPowerThresh_pct           %10.2f %10.2f %10s",
		mTxLowPowerThresh_pct,
		mRxLowPowerThresh_pct,
		asString_Qx(mQxLowPowerThresh_pct));

	// Low power alarm.
	Prn::print(aPF, "LowPowerAlarmEnable          %10s %10s %10s",
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

	// VSWR trigger.
	Prn::print(aPF, "VSWRTrigger                  %10d %10d %10s",
		mTxVSWRTrigger,
		mRxVSWRTrigger,
		asString_Qx(mQxVSWRTrigger));

	// VSWR alarm.
	Prn::print(aPF, "VSWRAlarmEnable              %10s %10s %10s",
		my_string_from_bool(mTxVSWRAlarmEnable),
		my_string_from_bool(mRxVSWRAlarmEnable),
		asString_Qx(mQxVSWRAlarmEnable));

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

	// Relay energize on alarm enable.
	Prn::print(aPF, "RelayOnAlarmAlarmEnable      %10s %10s %10s",
		my_string_from_bool(mTxRelayOnAlarmEnable),
		my_string_from_bool(mRxRelayOnAlarmEnable),
		asString_Qx(mQxRelayOnAlarmEnable));

	// VSWR on zero power.
	Prn::print(aPF, "VSWROnZeroEnable             %10s %10s %10s",
		my_string_from_bool(mTxVSWROnZeroEnable),
		my_string_from_bool(mRxVSWROnZeroEnable),
		asString_Qx(mQxVSWROnZeroEnable));

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

void SuperSettingsACM::requestReadAllSettings()
{
	mQxReadAllSettings = cQx_Request;
}
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
void SuperSettingsACM::requestVSWRTrigger(int aValue)
{
	mTxVSWRTrigger = aValue;
	mQxVSWRTrigger = cQx_Request;
}
void SuperSettingsACM::requestVSWRAlarmEnable(bool aValue)
{
	mTxVSWRAlarmEnable = aValue;
	mQxVSWRAlarmEnable = cQx_Request;
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
void SuperSettingsACM::requestRelayOnAlarmEnable(bool aValue)
{
	mTxRelayOnAlarmEnable = aValue;
	mQxRelayOnAlarmEnable = cQx_Request;
}
void SuperSettingsACM::requestVSWROnZeroEnable(bool aValue)
{
	mTxVSWROnZeroEnable = aValue;
	mQxVSWROnZeroEnable = cQx_Request;
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
// Return the super settings receive variables encoded into a json string.

std::string SuperSettingsACM::asJsonString()
{
	Json::Value tValue;
	char tBuffer[40];

	tValue["LowPowerThresh_pct"] = my_string_from_float(tBuffer, "%.2f", mRxLowPowerThresh_pct);
	tValue["LowPowerAlarmEnable"] = mRxLowPowerAlarmEnable;
	tValue["HighPowerThresh_pct"] = my_string_from_float(tBuffer, "%.2f", mRxHighPowerThresh_pct);
	tValue["HighPowerAlarmEnable"] = mRxHighPowerAlarmEnable;
	tValue["VSWRTrigger"] = mRxVSWRTrigger;
	tValue["VSWRAlarmEnable"] = mRxVSWRAlarmEnable;
	tValue["ForwardGain"] = mRxForwardGain;
	tValue["ReverseGain"] = mRxReverseGain;
	tValue["LatchAlarmEnable"] = mRxLatchAlarmEnable;
	tValue["PowerUpAlarmEnable"] = mRxPowerUpAlarmEnable;
	tValue["RelayOnAlarmEnable"] = mRxRelayOnAlarmEnable;
	tValue["VSWROnZeroEnable"] = mRxVSWROnZeroEnable;
	tValue["PTTDelay_sec"] = my_string_from_float(tBuffer, "%.2f", mRxPTTDelay_sec);
	tValue["PTTAlarmEnable"] = mRxPTTAlarmEnable;

	std::string tString;
	Json::FastWriter tWriter;
	tString = tWriter.write(tValue);
	return tString;

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
} //namespace

#if 0
RxLowPowerThresh_pct RxLowPowerThresh_pct
RxLowPowerAlarmEnable RxLowPowerAlarmEnable
RxHighPowerThresh_pct RxHighPowerThresh_pct
RxHighPowerAlarmEnable RxHighPowerAlarmEnable
RxVSWRTrigger RxVSWRTrigger
RxVSWRAlarmEnable RxVSWRAlarmEnable
RxForwardGain RxForwardGain
RxReverseGain RxReverseGain
RxLatchAlarmEnable RxLatchAlarmEnable
RxPowerUpAlarmEnable RxPowerUpAlarmEnable
RxRelayOnAlarmEnable RxRelayOnAlarmEnable
RxVSWROnZeroEnable RxVSWROnZeroEnable
RxPTTDelay_sec RxPTTDelay_sec
RxPTTAlarmEnable RxPTTAlarmEnable
#endif
 