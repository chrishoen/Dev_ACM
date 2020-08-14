#pragma once

/*==============================================================================
Shared memory and super state php extension library.
==============================================================================*/

#include "phpcpp.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Test variables.

// Set shared memory test variables.
void share_set_X1_Int(Php::Parameters& aP);
void share_set_X2_Int(Php::Parameters& aP);
void share_set_X3_Int(Php::Parameters& aP);
void share_set_X4_Int(Php::Parameters& aP);

// Get shared memory test variables.
Php::Value share_get_X1_Int();
Php::Value share_get_X2_Int();
Php::Value share_get_X3_Int();
Php::Value share_get_X4_Int();

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Super state variables.

// Set the test mode for both the da and tta.
// Pass int one parameter that is an integer test mode timeout.
void share_set_SuperStateBoth_TestMode_None();
void share_set_SuperStateBoth_TestMode_TerminateA(Php::Parameters& aP);
void share_set_SuperStateBoth_TestMode_TerminateB(Php::Parameters& aP);
void share_set_SuperStateBoth_TestMode_AntSweep(Php::Parameters& aP);
void share_set_SuperStateBoth_TestMode_BypassDA(Php::Parameters& aP);
void share_set_SuperStateBoth_TestMode_BypassTTA(Php::Parameters& aP);
void share_set_SuperStateBoth_TestMode_BypassBoth(Php::Parameters& aP);

// Set da want variables.
void share_set_SuperStateDA_UserAtten_Float(Php::Parameters& aP);

// Set tta want variables.
// Note: _AB means it will accept "A" or "a' or "b" or "B".
void share_set_SuperStateTTA_PreferRFPath_AB(Php::Parameters& aP);
void share_set_SuperStateTTA_Aux12VEnable_Bool(Php::Parameters& aP);

// Get all of the super state variables encoded into a json string.
Php::Value share_get_SuperStateTTA_Json();
Php::Value share_get_SuperStateDA_Json();
Php::Value share_get_SuperStateCU_Json();

// Get the mode info.
Php::Value share_get_ModeInfo_Json();

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Gain calculation variables.

// Set shared memory gain calculation variables.
void share_set_GainCalc_AttenSetting_Float(Php::Parameters& aP);
void share_set_GainCalc_AntJumperLoss_Float(Php::Parameters& aP);
void share_set_GainCalc_AntFeedlineLoss_Float(Php::Parameters& aP);
void share_set_GainCalc_SurgeProtLoss_Float(Php::Parameters& aP);
void share_set_GainCalc_InsideJumperLoss_Float(Php::Parameters& aP);
void share_set_GainCalc_RxJumperLoss_Float(Php::Parameters& aP);
void share_set_GainCalc_RMCGain_Float(Php::Parameters& aP);
void share_set_GainCalc_DesiredRxGain_Float(Php::Parameters& aP);

void share_set_GainCalc_TestportFeedlineLoss_Float(Php::Parameters& aP);
void share_set_GainCalc_TestportSurgeProtLoss_Float(Php::Parameters& aP);
void share_set_GainCalc_TestportJumperLoss_Float(Php::Parameters& aP);
void share_set_GainCalc_TestCable4Loss_Float(Php::Parameters& aP);
void share_set_GainCalc_RSSILevel_Float(Php::Parameters& aP);

// Get all of the super state variables encoded into a json string.
Php::Value share_get_GainCalc_Json();

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Gain calculation operations.

// Lock the json file and read from it. Do this before a read, modify, write
// operation.
void share_do_GainCalc_ReadModifyWriteBegin();

// Perform the calculation, write to the json file, and unlock it. Do this
// after a read, modify, write operation.
void share_do_GainCalc_ReadModifyWriteEnd();

// Lock the json file, read from it, and unlock it.
void share_do_GainCalc_ProtectedRead();

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Aux alarm modes.

// Set auxiliary alarm modes, user input 1..5.
void share_set_AuxAlarmMode_Low_Int(Php::Parameters& aP);
void share_set_AuxAlarmMode_High_Int(Php::Parameters& aP);
void share_set_AuxAlarmMode_Test_Int(Php::Parameters& aP);

// Set auxiliary alarm enables, user input 1..5. , bool enable
void share_set_AuxAlarmEnable_Int_Bool(Php::Parameters& aP);

// Get all of the variables encoded into a json string.
Php::Value share_get_AuxAlarmMode_Json();

//******************************************************************************
//******************************************************************************
//******************************************************************************
// System information.

// Get all of the system infromation variables encoded into a json string.
Php::Value share_get_SysInfo_Json();

//******************************************************************************
//******************************************************************************
//******************************************************************************
// System time.

// Get the system local time as a formatted string.
Php::Value share_get_SystemTime();

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Event notification queue.

// Attempt to read a string from the event notification queue. If the queue
// is not empty then read the string and return it. If it is empty then return
// a null strring.
Php::Value share_tryEventNotifyQueueRead();

// Advance the event notification queue read index after using a string from
// the above try read call. Do no call this if the above read call returned
// a null string because there's nothing to advance.
void share_finishEventNotifyQueueRead();

//******************************************************************************
//******************************************************************************
//******************************************************************************

#if 0

// Here is an example of performing the gain calculation with an
// update for a single input variable.a

// Lock the json file and read from it.
share_do_GainCalc_ReadModifyWriteBegin();

// Set the input variable.
share_set_GainCalc_AntJumperLoss_Float(2.0);

// Do the calculation on all of the variables, including the
// new one thatjust got set. Write to the json file and then
// unlock it.
share_do_GainCalc_ReadModifyWriteEnd();

// Show.



#endif

