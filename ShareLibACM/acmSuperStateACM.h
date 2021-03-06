#pragma once

/*==============================================================================
ACM super state structs.
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
// This contains a set of variables that encapculate the super state
// for an ACM. These are variables that are sent from a ACM to acmproc.
// These variables reflect the state of a ACM.
//
// This class is designed such that instances will reside in shared memory. 

class SuperStateACM
{
public:
	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Members.

	// True if this contains valid data.
	bool mValidFlag;

	// Increments at the program timer update.
	int mActiveCount;
	// Increments for each recieve.
	int mRxCount;

	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Members.

	// Measurement variables.
	float  mForwardPower_kw;
	float  mReflectedPower_kw;
	float  mForwardPower_dbm;
	float  mReflectedPower_dbm;
	float  mVSWR;
	float  mReturnLoss_db;
	float  mRho;
	float  mEfficiency_pct;

	// Alarm variables.
	bool   mAlarmOnZeroPower;

	// Alarm variables.
	bool   mAlarmFlag;
	bool   mAlarmSource_LowPower;
	bool   mAlarmSource_HighPower;
	bool   mAlarmSource_Vswr;
	bool   mAlarmSource_PowerUp;
	bool   mAlarmSource_PTT;

	// Overreide variables.
	float  mOverrideForwardPower_w;
	float  mOverrideReflectedPower_w;

	// Flag variables.
	bool mLowPowerAlarmEnable;
	bool mHighPowerAlarmEnable;
	bool mVSWRAlarmEnable;
	bool mLatchAlarmEnable;
	bool mPowerUpAlarmEnable;
	bool mRelayOnAlarmEnable;
	bool mVSWROnZeroEnable;
	bool mPTTAlarmEnable;

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

	// Update some variables by decoding a received response string from a
	// sent command. 
	bool updateForT(std::string* aResponse);

	// Update flag variables.
	void updateFlags(int aFlags);

	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Methods.

	// Return the super state encoded into a json string.
	std::string asJsonString();

	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Methods.

	// Apply limits to a variable. Needed for the json stuff.
	void doApplyLimits(float& aX);

};

//******************************************************************************
//******************************************************************************
//******************************************************************************
} //namespace

