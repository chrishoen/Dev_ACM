#pragma once

/*==============================================================================
ACM super state structs.
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
// This class contains a set of variables that encapculate the super wants
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
	// Test variables.
	int    mCount;
	int    mCode;

	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Members.

	// Wants variables.
	// value wanted.
	// request flag. If true then the want value is requested.
	// ack code, none, ack, nak. This is set after the want is verified.

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

	// Request the setting of want variables. 
	void requestThreshHighPower(float aValue);
	void requestThreshLowPower(float aValue);
	void requestThreshVSWR(float aValue);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
} //namespace
