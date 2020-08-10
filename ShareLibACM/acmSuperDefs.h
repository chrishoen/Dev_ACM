#pragma once

/*==============================================================================
DA andf TTA super state common definitions.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constants.

// Operating modes.
static const int cOpMode_Normal = 0;
static const int cOpMode_Test = 1;
static const int cOpMode_Diagnostics = 2;

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constants.

// DA test modes.
static const int cDA_TestMode_None = 0;
static const int cDA_TestMode_Bypass = 1 ;
static const int cDA_TestMode_AntSweep = 2;

// DA RF paths.
static const int cDA_RFPath_Normal = 0;
static const int cDA_RFPath_Bypass = 1;
static const int cDA_RFPath_TestBypass = 2;
static const int cDA_RFPath_TestAntSweep = 3;

// DA system type.
static const int cDA_SystemType_SA = 0;
static const int cDA_SystemType_ESS = 1;

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constants.

// TTA test modes.
static const int cTTA_TestMode_None = 0;
static const int cTTA_TestMode_Bypass = 1;
static const int cTTA_TestMode_AntSweep = 2;
static const int cTTA_TestMode_TerminateA = 3;
static const int cTTA_TestMode_TerminateB = 4;

// TTA RF paths.
static const int cTTA_RFPath_A = 0;
static const int cTTA_RFPath_B = 1;
static const int cTTA_RFPath_Bypass = 2;
static const int cTTA_RFPath_TestTermA = 3;
static const int cTTA_RFPath_TestTermB = 4;
static const int cTTA_RFPath_TestAntSweep = 5;
static const int cTTA_RFPath_TestBypass = 6;

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constants.

// System test modes.
static const int cSys_TestMode_None = 0;
static const int cSys_TestMode_BypassDA = 1;
static const int cSys_TestMode_BypassTTA = 2;
static const int cSys_TestMode_BypassBoth = 3;
static const int cSys_TestMode_AntSweep = 4;
static const int cSys_TestMode_TerminateA = 5;
static const int cSys_TestMode_TerminateB = 6;

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Methods.

// Return a variable as a string.
char* get_OpMode_asString(int aOpMode);

// Return a state variable as a string.
char* get_DA_TestMode_asString(int aTestMode);
char* get_DA_RFPath_asString(int aRFPath);
char* get_DA_SystemType_asString(int aSystemType);

// Return a state variable as a string.
char* get_TTA_TestMode_asString(int aTestMode);
char* get_TTA_RFPath_asString(int aRFPath);

// Return a state variable as a string.
char* get_Sys_TestMode_asString(int aTestMode);
char* get_Sys_TestMode_asString2(int aTestMode);

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Methods.

// Get a da test mode from a system test mode.
int get_DA_TestMode_from_Sys_TestMode(int aTestMode);

// Get a da test mode from a system test mode.
int get_TTA_TestMode_from_Sys_TestMode(int aTestMode);

//******************************************************************************
//******************************************************************************
//******************************************************************************

