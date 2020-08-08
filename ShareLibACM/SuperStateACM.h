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
// This struct contains a set of variables that encapculate the super state
// for a ACM. These are variables that are sent from a ACM to cproc.
// These variables reflect the state of a ACM.
//
// This class is designed such that instances will reside in shared memory. 
// It is also designed such that the .cpp file can be copied to the atmel
// code as a .c file.

typedef struct SuperStateACM
{
	// True if the struct has been written to.
	int mValidFlag;

	// Test variables.
	int    mCount;
	int    mCode;

   // Measurement variables.
   float  mTemperature;             // degree C
   float  mAmpCurrentA;             // amps
   float  mAmpCurrentB;             // amps
   float  mAmpVoltageA;             // volts
   float  mAmpVoltageB;             // volts
   float  mMainVoltage;             // volts
   float  mMainCurrent;             // amps
   float  mVccVoltage;              // volts
   float  mVbbVoltage;              // volts
   float  mAuxVoltage;              // volts
   float  mAuxCurrent;              // amps

	// Status variables.
	int    mLedCpuBoot;              // 0 = off
	int    mAmpAReg;                 // 0 = disabled
	int    mAmpBReg;                 // 0 = disabled 
	int    mAux12VoltPower;          // 0 = error
	int    mAmpARegFlag5Volts;       // 0 = error
	int    mAmpBRegFlag5Volts;       // 0 = error
	int    mRegFlag3p3Volts;         // 0 = error
	float  mRFAttenA1;               // float* 0.25 = db
	float  mRFAttenA2;               // float* 0.25 = db
	float  mRFAttenB1;               // float* 0.25 = db
	float  mRFAttenB2;               // float* 0.25 = db
	int    mTerminateLNAMode;        // 0 = not in terminate test mode
	int    mAntSweepMode;            // 0 = not in ant sweep test mode
	int    mLNABypass;               // 0 = not in bypass
	int    mAntTermRelay;            // 0 = not relayed
	int    mLNASelectRelay;          // 0 = not relayed  
	int    mLNASelectSwitch;         // 0 = A 1 = B

	// Operating variables.
	int    mOpMode;                  // 0 = autonomous 1 = test 2 = diagnostics
	int    mRFPath;                  // 0 = A 1 = B 2 = bypass
	int    mPreferRFPath;            // 0 = A 1 = B
	int    mTestModeTimeout;         // seconds 
	int    mTestModeExit;            // 0 = false 

} SuperStateACM;

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This struct contains a set of variables that encapculate the super wants
// for a ACM. These are sent from cproc to a ACM. They reflect variables that
// cproc wants to set for the ACM.

typedef struct SuperWantsACM
{
	// Test variables.
	int    mCount;
	int    mCode;

	// Wants variables.
	int    mPreferRFPath;            // 0 = A 1 = B
	int    mPreferRFPathFlag;        // 1 = update the variable
	int    mTestMode;                // 0 = none
	int    mTestModeTimeout;         // seconds 
	int    mTestModeFlag;            // 1 = update the variable
	int    mAux12VEnable;            // 0 = disable
	int    mAux12VEnableFlag;        // 1 = update the variable
	int    mEventCode;               // test event code
	int    mEventCodeFlag;           // 1 = update the variable

} SuperWantsACM;

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Methods.

// Initialize.
void SuperStateACM_initialize(SuperStateACM* aX);
void SuperWantsACM_initialize(SuperWantsACM* aX);

// Set to default test values.
void SuperStateACM_setNominals(SuperStateACM* aX);
void SuperStateACM_setDefaults(SuperStateACM* aX);
void SuperWantsACM_setDefaults(SuperWantsACM* aX);

// CopyTo copies from a superstate to a transmit buffer.
// CopyFrom copies from a receive buffer to a superstate.
// Values are encoded or decoded in ascii form. There are no labels
// or key:value pairs, order is the only thing that matters.
void SuperStateACM_copyTo(SuperStateACM* aX, char* aBuffer);
void SuperStateACM_copyFrom(SuperStateACM* aX, const char* aBuffer);
void SuperWantsACM_copyTo(SuperWantsACM* aX, char* aBuffer);
void SuperWantsACM_copyFrom(SuperWantsACM* aX, const char* aBuffer);

// Reset flags. Call this after sending a message so that the wanted
// values will only be processed once.
void SuperWantsACM_clearFlags(SuperWantsACM* aX);

//******************************************************************************
//******************************************************************************
//******************************************************************************

