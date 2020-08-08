//******************************************************************************
//******************************************************************************
//******************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SuperStateACM.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize.

void SuperStateACM_initialize(SuperStateACM* aX)
{
	aX->mValidFlag = 0;

	aX->mCount = 0;
	aX->mCode = 0;

	aX->mTemperature = 0.0;
	aX->mAmpCurrentA = 0.0;
	aX->mAmpCurrentB = 0.0;
	aX->mAmpVoltageA = 0.0;
	aX->mAmpVoltageB = 0.0;
	aX->mMainVoltage = 0.0;
	aX->mMainCurrent = 0.0;
	aX->mVccVoltage = 0.0;
	aX->mVbbVoltage = 0.0;
	aX->mAuxVoltage = 0.0;
	aX->mAuxCurrent = 0.0;

	aX->mLedCpuBoot = 0;
	aX->mAmpAReg = 0;
	aX->mAmpBReg = 0;
	aX->mAux12VoltPower = 0;
	aX->mAmpARegFlag5Volts = 0;
	aX->mAmpBRegFlag5Volts = 0;
	aX->mRegFlag3p3Volts = 0;
	aX->mRFAttenA1 = 0.0;
	aX->mRFAttenA2 = 0.0;
	aX->mRFAttenB1 = 0.0;
	aX->mRFAttenB2 = 0.0;
	aX->mTerminateLNAMode = 0;
	aX->mAntSweepMode = 0;
	aX->mLNABypass = 0;
	aX->mAntTermRelay = 0;
	aX->mLNASelectRelay = 0;
	aX->mLNASelectSwitch = 0;

	aX->mOpMode = 0;
	aX->mRFPath = 0;
	aX->mPreferRFPath = 0;
	aX->mTestModeTimeout = 0;
	aX->mTestModeExit = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize.

void SuperStateACM_setNominals(SuperStateACM* aX)
{
	aX->mValidFlag = 1;

	aX->mCount = 0;
	aX->mCode = 0;

	aX->mTemperature = 22.0;
	aX->mAmpCurrentA = 0.4;
	aX->mAmpCurrentB = 0.4;
	aX->mAmpVoltageA = 10.0;
	aX->mAmpVoltageB = 10.0;
	aX->mMainVoltage = 10.0;
	aX->mMainCurrent = 0.6;
	aX->mVccVoltage = 10.0;
	aX->mVbbVoltage = 10.0;
	aX->mAuxVoltage = 10.0;
	aX->mAuxCurrent = 10.0;

	aX->mLedCpuBoot = 0;
	aX->mAmpAReg = 0;
	aX->mAmpBReg = 0;
	aX->mAux12VoltPower = 0;
	aX->mAmpARegFlag5Volts = 0;
	aX->mAmpBRegFlag5Volts = 0;
	aX->mRegFlag3p3Volts = 0;
	aX->mRFAttenA1 = 0.0;
	aX->mRFAttenA2 = 0.0;
	aX->mRFAttenB1 = 0.0;
	aX->mRFAttenB2 = 0.0;
	aX->mTerminateLNAMode = 0;
	aX->mAntSweepMode = 0;
	aX->mLNABypass = 0;
	aX->mAntTermRelay = 0;
	aX->mLNASelectRelay = 0;
	aX->mLNASelectSwitch = 0;

	aX->mOpMode = 0;
	aX->mRFPath = 0;
	aX->mPreferRFPath = 0;
	aX->mTestModeTimeout = 0;
	aX->mTestModeExit = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Set to default test values.

void SuperStateACM_setDefaults(SuperStateACM* aX)
{
	aX->mValidFlag = 1;

	aX->mCount = 0;
	aX->mCode = 0;

	aX->mTemperature = 1.1;
	aX->mAmpCurrentA = 2.1;
	aX->mAmpCurrentB = 3.1;
	aX->mAmpVoltageA = 4.1;
	aX->mAmpVoltageB = 5.1;
	aX->mMainVoltage = 6.1;
	aX->mMainCurrent = 7.1;
	aX->mVccVoltage = 8.1;
	aX->mVbbVoltage = 9.1;
	aX->mAuxVoltage = 10.1;
	aX->mAuxCurrent = 11.1;

	aX->mLedCpuBoot = 12;
	aX->mAmpAReg = 13;
	aX->mAmpBReg = 14;
	aX->mAux12VoltPower = 15;
	aX->mAmpARegFlag5Volts = 16;
	aX->mAmpBRegFlag5Volts = 17;
	aX->mRegFlag3p3Volts = 18;
	aX->mRFAttenA1 = 19.1;
	aX->mRFAttenA2 = 20.1;
	aX->mRFAttenB1 = 21.1;
	aX->mRFAttenB2 = 22.1;
	aX->mTerminateLNAMode = 23;
	aX->mAntSweepMode = 24;
	aX->mLNABypass = 25;
	aX->mAntTermRelay = 26;
	aX->mLNASelectRelay = 27;
	aX->mLNASelectSwitch = 28;

	aX->mOpMode = 29;
	aX->mRFPath = 30;
	aX->mPreferRFPath = 31;
	aX->mTestModeTimeout = 32;
	aX->mTestModeExit = 33;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize.

void SuperWantsACM_initialize(SuperWantsACM* aX)
{
	aX->mCount = 0;
	aX->mCode = 0;

	aX->mPreferRFPath = 0;
	aX->mPreferRFPathFlag = 0;
	aX->mTestMode = 0;
	aX->mTestModeTimeout = 0;
	aX->mTestModeFlag = 0;
	aX->mAux12VEnable = 0;
	aX->mAux12VEnableFlag = 0;
	aX->mEventCode = 0;
	aX->mEventCodeFlag = 0;
}

void SuperWantsACM_setDefaults(SuperWantsACM* aX)
{
	aX->mCount = 0;
	aX->mCode = 0;

	aX->mPreferRFPath = 1;
	aX->mPreferRFPathFlag = 2;
	aX->mTestMode = 3;
	aX->mTestModeTimeout = 4;
	aX->mTestModeFlag = 5;
	aX->mAux12VEnable = 6;
	aX->mAux12VEnableFlag = 7;
	aX->mEventCode = 0;
	aX->mEventCodeFlag = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Copy.

void SuperStateACM_copyTo(SuperStateACM* aX, char* aBuffer)
{
	sprintf(aBuffer, "%d,%d,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%d,%d,%d,%d,%d,%d,%d,%.4f,%.4f,%.4f,%.4f,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
		aX->mCount,
		aX->mCode,
		aX->mTemperature,
		aX->mAmpCurrentA,
		aX->mAmpCurrentB,
		aX->mAmpVoltageA,
		aX->mAmpVoltageB,
		aX->mMainVoltage,
		aX->mMainCurrent,
		aX->mVccVoltage,
		aX->mVbbVoltage,
		aX->mAuxVoltage,
		aX->mAuxCurrent,
		aX->mLedCpuBoot,
		aX->mAmpAReg,
		aX->mAmpBReg,
		aX->mAux12VoltPower,
		aX->mAmpARegFlag5Volts,
		aX->mAmpBRegFlag5Volts,
		aX->mRegFlag3p3Volts,
		aX->mRFAttenA1,
		aX->mRFAttenA2,
		aX->mRFAttenB1,
		aX->mRFAttenB2,
		aX->mTerminateLNAMode,
		aX->mAntSweepMode,
		aX->mLNABypass,
		aX->mAntTermRelay,
		aX->mLNASelectRelay,
		aX->mLNASelectSwitch,
		aX->mOpMode,
		aX->mRFPath,
		aX->mPreferRFPath,
		aX->mTestModeTimeout,
		aX->mTestModeExit);
}

void SuperStateACM_copyFrom(SuperStateACM* aX, const char* aBuffer)
{
	sscanf(aBuffer, "%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d,%d,%d,%d,%d,%d,%d,%f,%f,%f,%f,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
		&aX->mCount,
		&aX->mCode,
		&aX->mTemperature,
		&aX->mAmpCurrentA,
		&aX->mAmpCurrentB,
		&aX->mAmpVoltageA,
		&aX->mAmpVoltageB,
		&aX->mMainVoltage,
		&aX->mMainCurrent,
		&aX->mVccVoltage,
		&aX->mVbbVoltage,
		&aX->mAuxVoltage,
		&aX->mAuxCurrent,
		&aX->mLedCpuBoot,
		&aX->mAmpAReg,
		&aX->mAmpBReg,
		&aX->mAux12VoltPower,
		&aX->mAmpARegFlag5Volts,
		&aX->mAmpBRegFlag5Volts,
		&aX->mRegFlag3p3Volts,
		&aX->mRFAttenA1,
		&aX->mRFAttenA2,
		&aX->mRFAttenB1,
		&aX->mRFAttenB2,
		&aX->mTerminateLNAMode,
		&aX->mAntSweepMode,
		&aX->mLNABypass,
		&aX->mAntTermRelay,
		&aX->mLNASelectRelay,
		&aX->mLNASelectSwitch,
		&aX->mOpMode,
		&aX->mRFPath,
		&aX->mPreferRFPath,
		&aX->mTestModeTimeout,
	   &aX->mTestModeExit);

 	aX->mValidFlag = 1;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Copy.

void SuperWantsACM_copyTo(SuperWantsACM* aX, char* aBuffer)
{
	sprintf(aBuffer, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
		aX->mCount,
		aX->mCode,
		aX->mPreferRFPath,
		aX->mPreferRFPathFlag,
		aX->mTestMode,
		aX->mTestModeTimeout,
		aX->mTestModeFlag,
		aX->mAux12VEnable,
	   aX->mAux12VEnableFlag,
	   aX->mEventCode,
		aX->mEventCodeFlag);
}

void SuperWantsACM_copyFrom(SuperWantsACM* aX, const char* aBuffer)
{
	sscanf(aBuffer, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
		&aX->mCount,
		&aX->mCode,
		&aX->mPreferRFPath,
		&aX->mPreferRFPathFlag,
		&aX->mTestMode,
		&aX->mTestModeTimeout,
		&aX->mTestModeFlag,
		&aX->mAux12VEnable,
   	&aX->mAux12VEnableFlag,
	   &aX->mEventCode,
		&aX->mEventCodeFlag);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Reset flags. Call this after sending a message so that the wanted
// values will only be processed once.

void SuperWantsACM_clearFlags(SuperWantsACM* aX)
{
	aX->mPreferRFPathFlag = 0;
   aX->mTestModeFlag = 0;
   aX->mAux12VEnableFlag = 0;
	aX->mEventCodeFlag = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

#if 0
float  mTemperature
float  mAmpCurrentA
float  mAmpCurrentB
float  mAmpVoltageA
float  mAmpVoltageB
float  mMainVoltage
float  mMainCurrent
float  mVccVoltage
float  mVbbVoltage
float  mAuxVoltage
float  mAuxCurrent
int    mLedCpuBoot
int    mAmpAReg
int    mAmpBReg
int    mAux12VoltPower
int    mAmpARegFlag5Volts
int    mAmpBRegFlag5Volts
int    mRegFlag3p3Volts
float  mRFAttenA1
float  mRFAttenA2
float  mRFAttenB1
float  mRFAttenB2
int    mTerminateLNAMode
int    mAntSweepMode
int    mLNABypass
int    mAntTermRelay
int    mLNASelectRelay
int    mLNASelectSwitch
int    mOpMode
int    mRFPath
int    mPreferRFPath

Temperature Temperature
AmpCurrentA AmpCurrentA
AmpCurrentB AmpCurrentA
AmpVoltageA AmpVoltageA
AmpVoltageB AmpVoltageB
MainVoltage MainVoltage
MainCurrent MainCurrent
VccVoltage VccVoltage
VbbVoltage VbbVoltage
AuxVoltage AuxVoltage
AuxCurrent AuxCurrent
LedCpuBoot LedCpuBoot
AmpAReg AmpAReg
AmpBReg AmpBReg
Aux12VoltPower Aux12VoltPower
AmpARegFlag5Volts AmpARegFlag5Volts
AmpBRegFlag5Volts AmpBRegFlag5Volts
RegFlag3p3Volts RegFlag3p3Volts
RFAttenA1 RFAttenA1
RFAttenA2 RFAttenA2
RFAttenB1 RFAttenB1
RFAttenB2 RFAttenB2
TerminateLNAMode TerminateLNAMode
AntSweepMode AntSweepMode
LNABypass LNABypass
AntTermRelay AntTermRelay
LNASelectRelay LNASelectRelay
LNASelectSwitch LNASelectSwitch
OpMode OpMode
RFPath RFPath
PreferRFPath PreferRFPath


#endif
