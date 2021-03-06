#pragma once

/*==============================================================================
ACM super settings.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <string>
#include "acmSuperDefs.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace ACM
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class contains a set of variables that encapculate the super settings
// for an ACM. These are sent from the user (web page) to acmproc. They reflect 
// variables that the user wants to set for the ACM.

class SuperSettingsACM
{
public:
	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Members.

	// True if this contains valid data.
	int mValidFlag;

	// Test variables.
	int    mCount;
	int    mCode;

	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Members.

	// Settings variables.
	// mTxVariable   the settings transmitted to    the acm
	// mRxVariable   the settings received    from  the acm
	// mQxVariable   the request code: none, request, pending, ack, nak

	// Read all settings.
	int    mQxReadAllSettings;

	// Low power threshold.
	float  mTxLowPowerThresh_pct;
	float  mRxLowPowerThresh_pct;
	int    mQxLowPowerThresh_pct;

	// Low power alarm.
	bool   mTxLowPowerAlarmEnable;
	bool   mRxLowPowerAlarmEnable;
	int    mQxLowPowerAlarmEnable;

	// High power threshold.
	float  mTxHighPowerThresh_pct;
	float  mRxHighPowerThresh_pct;
	int    mQxHighPowerThresh_pct;

	// High power alarm.
	bool   mTxHighPowerAlarmEnable;
	bool   mRxHighPowerAlarmEnable;
	int    mQxHighPowerAlarmEnable;

	// VSWR trigger.
	int    mTxVSWRTrigger;
	int    mRxVSWRTrigger;
	int    mQxVSWRTrigger;

	// VSWR alarm.
	bool   mTxVSWRAlarmEnable;
	bool   mRxVSWRAlarmEnable;
	int    mQxVSWRAlarmEnable;

	// Gain.
	int    mTxForwardGain;
	int    mTxReverseGain;
	int    mRxForwardGain;
	int    mRxReverseGain;
	int    mQxGain;

	// Latch alarm enable.
	bool   mTxLatchAlarmEnable;
	bool   mRxLatchAlarmEnable;
	int    mQxLatchAlarmEnable;

	// Power up alarm enable.
	bool   mTxPowerUpAlarmEnable;
	bool   mRxPowerUpAlarmEnable;
	int    mQxPowerUpAlarmEnable;

	// Relay energize on alarm enable.
	bool   mTxRelayOnAlarmEnable;
	bool   mRxRelayOnAlarmEnable;
	int    mQxRelayOnAlarmEnable;

	// VSWR on zero power.
	bool   mTxVSWROnZeroEnable;
	bool   mRxVSWROnZeroEnable;
	int    mQxVSWROnZeroEnable;

	// PTT delay.
	float  mTxPTTDelay_sec;
	float  mRxPTTDelay_sec;
	int    mQxPTTDelay_sec;

	// PTT alarm.
	bool   mTxPTTAlarmEnable;
	bool   mRxPTTAlarmEnable;
	int    mQxPTTAlarmEnable;

	// Clear alarms.
	bool   mTxClearAlarms;
	bool   mRxClearAlarms;
	int    mQxClearAlarms;

	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Methods.

	// Initialize. There's no constructor because of shared memory. 
	void initialize();

	// Show.
	void show(int aPrintFilter = 0);

	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Methods.

	// Request the setting of settings variables. 
	void requestReadAllSettings();

	// Request the setting of settings variables. 
	void requestLowPowerThresh_pct(float aValue);
	void requestLowPowerAlarmEnable(bool aValue);
	void requestHighPowerThresh_pct(float aValue);
	void requestHighPowerAlarmEnable(bool aValue);
	void requestVSWRTrigger(int aValue);
	void requestVSWRAlarmEnable(bool aValue);
	void requestGain(int aForward, int aReverse);
	void requestLatchAlarmEnable(bool aValue);
	void requestPowerUpAlarmEnable(bool aValue);
	void requestRelayOnAlarmEnable(bool aValue);
	void requestVSWROnZeroEnable(bool aValue);
	void requestPTTDelay_sec(float aValue);
	void requestPTTAlarmEnable(bool aValue);
	void requestClearAlarms();

	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Methods.

	// Return the super settings receive variables encoded into a json string.
	std::string asJsonString();
};


//******************************************************************************
//******************************************************************************
//******************************************************************************
} //namespace


#if 0
mQxLowPowerThresh_pct;
mQxLowPowerAlarmEnable;
mQxHighPowerThresh_pct;
mQxHighPowerAlarmEnable;
mQxGain;
mQxLatchAlarmEnable;
mQxPowerUpAlarmEnable;
mQxRelayOnAlarmEnable;
mQxRelayOnVSWREnable;
mQxVSWROnZeroEnable;
mQxPTTDelay_sec;
mQxPTTAlarmEnable;
#endif