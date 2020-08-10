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
	int mValidFlag;

	// Test variables.
	int mCount;
	int mCode;

	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Members.

	// Measurement variables.
	float  mForwardPower_kw;
	float  mReflectedPower_kw;
	float  mVSWR;
	float  mReturnLoss_db;
	float  mRho;
	float  mEfficiency_pct;

	// Alarm variables.
	bool   mAlarmFlag;
	bool   mAlarmOnZeroPower;

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
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
} //namespace

