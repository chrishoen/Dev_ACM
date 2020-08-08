#pragma once

/*==============================================================================
ACM super state structs.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "SuperStateDefs.h"

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
	//******************************************************************************
	//******************************************************************************
	//******************************************************************************
	// Members.

	// True if this contains valid data.
	int mValidFlag;

	// Test variables.
	int mCount;
	int mCode;

	//*****************************************************************************
	//*****************************************************************************
	//*****************************************************************************
	// Members.
	
	// Measurement variables.
	float  mForwardPower_kw;
	float  mForwardPower_dbm;
	float  mReflectedPower_kw;
	float  mReflectedPower_dbm;
	float  mVSWR;
	float  mReturnLoss_db;
	float  mRho;
	float  mEfficiency_percent;

	//*****************************************************************************
	//*****************************************************************************
	//*****************************************************************************
	// Methods.

	// Initialize. There's no constructor because of shared memory. 
	void initialize();

	// Show.
	void show(int aPrintFilter = 0);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This struct contains a set of variables that encapculate the super wants
// for an ACM. These are sent from the user (web page) to acmproc. They reflect 
// variables that the user wants to set for the ACM.

class SuperWantsACM
{
public:
	//******************************************************************************
	//******************************************************************************
	//******************************************************************************
	// Members.

	// True if this contains valid data.
	int mValidFlag;

	// Test variables.
	// Test variables.
	int    mCount;
	int    mCode;

	//******************************************************************************
	//******************************************************************************
	//******************************************************************************
	// Members.

	// Wants variables.
	float  mThreshHighPower_kw;
	bool   mThreshHighPower_Req;
	int    mThreshHighPower_Ack;

	// Wants variables.
	float  mThreshLowPower_kw;
	bool   mThreshLowPower_Req;
	int    mThreshLowPower_Ack;

	// Wants variables.
	float  mThreshVSWR;
	bool   mThreshVSWR_Req;
	int    mThreshVSWR_Ack;

	//*****************************************************************************
	//*****************************************************************************
	//*****************************************************************************
	// Methods.

	// Initialize. There's no constructor because of shared memory. 
	void initialize();

	// Show.
	void show(int aPrintFilter = 0);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************

