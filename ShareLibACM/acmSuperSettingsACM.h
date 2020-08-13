#pragma once

/*==============================================================================
ACM super settings.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

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

	// Relay energize on power alarm enable.
	bool   mTxRelayOnPowerEnable;
	bool   mRxRelayOnPowerEnable;
	int    mQxRelayOnPowerEnable;

	// Relay energize on VSWR alarm enable.
	bool   mTxRelayOnVSWREnable;
	bool   mRxRelayOnVSWREnable;
	int    mQxRelayOnVSWREnable;

	// Check VSWR on zero power.
	bool   mTxCheckVSWROnZeroEnable;
	bool   mRxCheckVSWROnZeroEnable;
	int    mQxCheckVSWROnZeroEnable;

	// PTT delay.
	float  mTxPTTDelay_sec;
	float  mRxPTTDelay_sec;
	int    mQxPTTDelay_sec;

	// PTT alarm.
	bool   mTxPTTAlarmEnable;
	bool   mRxPTTAlarmEnable;
	int    mQxPTTAlarmEnable;

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
	void requestRelayOnPowerEnable(bool aValue);
	void requestRelayOnVSWREnable(bool aValue);
	void requestCheckVSWROnZeroEnable(bool aValue);
	void requestPTTDelay_sec(float aValue);
	void requestPTTAlarmEnable(bool aValue);

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
mQxRelayOnPowerEnable;
mQxRelayOnVSWREnable;
mQxCheckVSWROnZeroEnable;
mQxPTTDelay_sec;
mQxPTTAlarmEnable;
#endif