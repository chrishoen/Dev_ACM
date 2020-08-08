//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "SuperStateDefs.h"


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a super state variable as a string.

char* get_OpMode_asString(int aOpMode)
{
   switch (aOpMode)
   {
   case cOpMode_Normal: return "Normal";
   case cOpMode_Test: return "Test";
   case cOpMode_Diagnostics: return "Diagnostics";
   }
   return "UNKNOWN";
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a super state variable as a string.

char* get_DA_TestMode_asString(int aTestMode)
{
   switch (aTestMode)
   {
   case cDA_TestMode_None: return "None";
   case cDA_TestMode_Bypass: return "TestBypass";
   case cDA_TestMode_AntSweep: return "AntSweep";
   }
   return "UNKNOWN";
}

char* get_DA_RFPath_asString(int aRFPath)
{
   switch (aRFPath)
   {
   case cDA_RFPath_Normal: return "Normal";
   case cDA_RFPath_Bypass: return "Bypass";
   case cDA_RFPath_TestBypass: return "TestBypass";
   case cDA_RFPath_TestAntSweep: return "AntSweep";
   }
   return "UNKNOWN";
}

char* get_DA_SystemType_asString(int aSystemType)
{
   switch (aSystemType)
   {
   case cDA_SystemType_SA: return "SA";
   case cDA_SystemType_ESS: return "ESS";
   }
   return "UNKNOWN";
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a super state variable as a string.

char* get_TTA_TestMode_asString(int aTestMode)
{
   switch (aTestMode)
   {
   case cTTA_TestMode_None: return "None";
   case cTTA_TestMode_Bypass: return "TestBypass";
   case cTTA_TestMode_AntSweep: return "TestAntSweep";
   case cTTA_TestMode_TerminateA: return "TestTermA";
   case cTTA_TestMode_TerminateB: return "TestTermB";
   }
   return "UNKNOWN";
}

char* get_TTA_RFPath_asString(int aRFPath)
{
   switch (aRFPath)
   {
   case cTTA_RFPath_A: return "Amp A";
   case cTTA_RFPath_B: return "Amp B";
   case cTTA_RFPath_Bypass: return "Bypass";
   case cTTA_RFPath_TestTermA: return "TerminateA";
   case cTTA_RFPath_TestTermB: return "TerminateB";
   case cTTA_RFPath_TestAntSweep: return "AntSweep";
   case cTTA_RFPath_TestBypass: return "TestBypass";
   }
   return "UNKNOWN";
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a super state variable as a string.

char* get_Sys_TestMode_asString(int aTestMode)
{
   switch (aTestMode)
   {
   case cSys_TestMode_None:       return "None";
   case cSys_TestMode_BypassDA:   return "TestBypassDA";
   case cSys_TestMode_BypassTTA:  return "TestBypassTTA";
   case cSys_TestMode_BypassBoth: return "TestBypassBoth";
   case cSys_TestMode_AntSweep:   return "TestAntSweep";
   case cSys_TestMode_TerminateA: return "TestTermA";
   case cSys_TestMode_TerminateB: return "TestTermB";
   }
   return "UNKNOWN";
}

char* get_Sys_TestMode_asString2(int aTestMode)
{
   switch (aTestMode)
   {
   case cSys_TestMode_None:       return "None";
   case cSys_TestMode_BypassDA:   return "Bypass DA";
   case cSys_TestMode_BypassTTA:  return "Bypass TTA";
   case cSys_TestMode_BypassBoth: return "Bypass DA and TTA";
   case cSys_TestMode_AntSweep:   return "Antenna Sweep";
   case cSys_TestMode_TerminateA: return "Terminate A";
   case cSys_TestMode_TerminateB: return "Terminate B";
   }
   return "UNKNOWN";
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get a da test mode from a system test mode.

int get_DA_TestMode_from_Sys_TestMode(int aTestMode)
{
   switch (aTestMode)
   {
   case cSys_TestMode_None:       return cDA_TestMode_None;
   case cSys_TestMode_BypassDA:   return cDA_TestMode_Bypass;
   case cSys_TestMode_BypassTTA:  return cDA_TestMode_None;
   case cSys_TestMode_BypassBoth: return cDA_TestMode_Bypass;
   case cSys_TestMode_AntSweep:   return cDA_TestMode_AntSweep;
   case cSys_TestMode_TerminateA: return cDA_TestMode_None;
   case cSys_TestMode_TerminateB: return cDA_TestMode_None;
   }
   return 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get a da test mode from a system test mode.

int get_TTA_TestMode_from_Sys_TestMode(int aTestMode)
{
   switch (aTestMode)
   {
   case cSys_TestMode_None:       return cTTA_TestMode_None;
   case cSys_TestMode_BypassDA:   return cTTA_TestMode_None;
   case cSys_TestMode_BypassTTA:  return cTTA_TestMode_Bypass;
   case cSys_TestMode_BypassBoth: return cTTA_TestMode_Bypass;
   case cSys_TestMode_AntSweep:   return cTTA_TestMode_AntSweep;
   case cSys_TestMode_TerminateA: return cTTA_TestMode_TerminateA;
   case cSys_TestMode_TerminateB: return cTTA_TestMode_TerminateB;
   }
   return 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

