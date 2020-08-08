//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "json.h"
#include "SuperStateExtraACM.h"


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return the super state encoded into a json string.

std::string SuperStateACM_asJsonString(SuperStateACM* aX, bool aShow)
{
   Json::Value tOpModeList;
   tOpModeList.append("Normal");
   tOpModeList.append("Test");
   tOpModeList.append("Diagnostics");

   Json::Value tRFPathList;
   tRFPathList.append("A");
   tRFPathList.append("B");
   tRFPathList.append("Bypass");
   tRFPathList.append("TestTermA");
   tRFPathList.append("TestTermB");
   tRFPathList.append("TestAntSweep");
   tRFPathList.append("TestBypass");

   Json::Value tValue;
   tValue["Temperature"] = aX->mTemperature;
   tValue["AmpCurrentA"] = aX->mAmpCurrentA;
   tValue["AmpCurrentB"] = aX->mAmpCurrentB;
   tValue["AmpVoltageA"] = aX->mAmpVoltageA;
   tValue["AmpVoltageB"] = aX->mAmpVoltageB;
   tValue["MainVoltage"] = aX->mMainVoltage;
   tValue["MainCurrent"] = aX->mMainCurrent;
   tValue["VccVoltage"] = aX->mVccVoltage;
   tValue["VbbVoltage"] = aX->mVbbVoltage;
   tValue["AuxVoltage"] = aX->mAuxVoltage;
   tValue["AuxCurrent"] = aX->mAuxCurrent;

   tValue["LedCpuBoot"] = aX->mLedCpuBoot ? true : false;
   tValue["AmpAReg"] = aX->mAmpAReg ? true : false;
   tValue["AmpBReg"] = aX->mAmpBReg ? true : false;
   tValue["Aux12VoltPower"] = aX->mAux12VoltPower ? true : false;
   tValue["AmpARegFlag5Volts"] = aX->mAmpARegFlag5Volts ? true : false;
   tValue["AmpBRegFlag5Volts"] = aX->mAmpBRegFlag5Volts ? true : false;
   tValue["RegFlag3p3Volts"] = aX->mRegFlag3p3Volts ? true : false;
   tValue["RFAttenA1"] = aX->mRFAttenA1;
   tValue["RFAttenA2"] = aX->mRFAttenA2;
   tValue["RFAttenB1"] = aX->mRFAttenB1;
   tValue["RFAttenB2"] = aX->mRFAttenB2;
   tValue["TerminateLNAMode"] = aX->mTerminateLNAMode ? true : false;
   tValue["AntSweepMode"] = aX->mAntSweepMode ? true : false;
   tValue["LNABypass"] = aX->mLNABypass ? true : false;
   tValue["AntTermRelay"] = aX->mAntTermRelay ? true : false;
   tValue["LNASelectRelay"] = aX->mLNASelectRelay ? true : false;
   tValue["LNASelectSwitch"] = aX->mLNASelectSwitch ? "B" : "A";

   tValue["OpMode"] = tOpModeList[aX->mOpMode];
   tValue["OpModeList"] = tOpModeList;
   tValue["RFPath"] = tRFPathList[aX->mRFPath];
   tValue["RFPathList"] = tRFPathList;
   tValue["PreferRFPath"] = aX->mPreferRFPath ? "B" : "A";

   if (aShow)
   {
      std::cout << "SuperStateACM  " << tValue << std::endl;
   }

   std::string tString;
   Json::FastWriter tWriter;
   tString = tWriter.write(tValue);
   return tString;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void SuperStateACM_show(SuperStateACM* aX)
{
	printf("ACM SuperState *********************************************\n");
	printf("Count                  %10d\n", aX->mCount);
	printf("Code                   %10d\n", aX->mCode);
	printf("Temperature            %10.3f\n", aX->mTemperature);
	printf("AmpCurrentA            %10.3f\n", aX->mAmpCurrentA);
	printf("AmpCurrentB            %10.3f\n", aX->mAmpCurrentB);
	printf("AmpVoltageA            %10.3f\n", aX->mAmpVoltageA);
	printf("AmpVoltageB            %10.3f\n", aX->mAmpVoltageB);
	printf("MainVoltage            %10.3f\n", aX->mMainVoltage);
	printf("MainCurrent            %10.3f\n", aX->mMainCurrent);
	printf("VccVoltage             %10.3f\n", aX->mVccVoltage);
	printf("VbbVoltage             %10.3f\n", aX->mVbbVoltage);
	printf("AuxVoltage             %10.3f\n", aX->mAuxVoltage);
	printf("AuxCurrent             %10.3f\n", aX->mAuxCurrent);
	printf("LedCpuBoot             %10d\n", aX->mLedCpuBoot);
	printf("AmpAReg                %10d\n", aX->mAmpAReg);
	printf("AmpBReg                %10d\n", aX->mAmpBReg);
	printf("Aux12VoltPower         %10d\n", aX->mAux12VoltPower);
	printf("AmpARegFlag5Volts      %10d\n", aX->mAmpARegFlag5Volts);
	printf("AmpBRegFlag5Volts      %10d\n", aX->mAmpBRegFlag5Volts);
	printf("RegFlag3p3Volts        %10d\n", aX->mRegFlag3p3Volts);
	printf("RFAttenA1              %10.3f\n", aX->mRFAttenA1);
	printf("RFAttenA2              %10.3f\n", aX->mRFAttenA2);
	printf("RFAttenB1              %10.3f\n", aX->mRFAttenB1);
	printf("RFAttenB2              %10.3f\n", aX->mRFAttenB2);
	printf("TerminateLNAMode       %10d\n", aX->mTerminateLNAMode);
	printf("AntSweepMode           %10d\n", aX->mAntSweepMode);
	printf("LNABypass              %10d\n", aX->mLNABypass);
	printf("AntTermRelay           %10d\n", aX->mAntTermRelay);
	printf("LNASelectRelay         %10d\n", aX->mLNASelectRelay);
	printf("LNASelectSwitch        %10d\n", aX->mLNASelectSwitch);
   printf("OpMode                 %10s\n", get_OpMode_asString(aX->mOpMode));
	printf("\n");
}

void SuperStateACM_show2(SuperStateACM* aX)
{
	printf("ACM SuperState *********************************************\n");
	printf("TerminateLNAMode       %10d\n", aX->mTerminateLNAMode);
	printf("AntSweepMode           %10d\n", aX->mAntSweepMode);
	printf("LNABypass              %10d\n", aX->mLNABypass);
	printf("AntTermRelay           %10d\n", aX->mAntTermRelay);
	printf("LNASelectRelay         %10d\n", aX->mLNASelectRelay);
	printf("LNASelectSwitch        %10d\n", aX->mLNASelectSwitch);
	printf("\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void SuperWantsACM_show(SuperWantsACM* aX)
{
	printf("ACM SuperWants *********************************************\n");
	printf("Count                  %10d\n", aX->mCount);
	printf("Code                   %10d\n", aX->mCode);
	printf("PreferRFPath           %10d\n", aX->mPreferRFPath);
   printf("\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

