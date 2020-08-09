//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "SuperStateACM.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize.

void SuperStateACM::initialize()
{
	mForwardPower_kw = 0.0;
	mForwardPower_dbm = 0.0;
	mReflectedPower_kw = 0.0;
	mReflectedPower_dbm = 0.0;
	mVSWR = 0.0;
	mReturnLoss_db = 0.0;
	mRho = 0.0;
	mEfficiency_percent = 0.0;

   mAlarmFlag = false;
   mAlarmOnZeroPower = false;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void SuperStateACM::show(int aPF)
{
	Prn::print(aPF, "ForwardPower_kw      %10.2f", mForwardPower_kw);
   Prn::print(aPF, "ForwardPower_dbm     %10.2f", mForwardPower_dbm);
	Prn::print(aPF, "ReflectedPower_kw    %10.2f", mReflectedPower_kw);
   Prn::print(aPF, "ReflectedPower_dbm   %10.2f", mReflectedPower_dbm);
	Prn::print(aPF, "VSWR                 %10.2f", mVSWR);
	Prn::print(aPF, "ReturnLoss_db        %10.2f", mReturnLoss_db);
	Prn::print(aPF, "Rho                  %10.2f", mRho);
	Prn::print(aPF, "Efficiency_percent   %10.2f", mEfficiency_percent);
	Prn::print(aPF, "AlarmFlag            %10s", my_string_from_bool(mAlarmFlag));
	Prn::print(aPF, "AlarmOnZeroPower     %10s", my_string_from_bool(mAlarmOnZeroPower));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Update some variables by decoding a received response string from a
// sent command. 

bool SuperStateACM::updateForT(std::string* aResponse)
{
	// 012345678901234
	// >000.0,00.00A1
	const char* tBuffer = aResponse->c_str();
	float tForwardPower = -1;
	float tReflectedPower = -1;
	char  tAlarmChar = 'z';
	int   tAlarmOnZeroPower = 9;
	int   tRet = 0;

	// Guard.
	if ((tBuffer[0] != '>') ||
		(tBuffer[4] != '.') ||
		(tBuffer[6] != ',') ||
		(tBuffer[14] != 0)
		)
	{
		Prn::print(Prn::View21, "SuperStateACM::updateForT ERROR 101");
		return false;
	}

	// Read from response string into temp variables.
	tRet = sscanf(tBuffer, ">%f,%f%c%d",
		&tForwardPower,
		&tReflectedPower,
		&tAlarmChar,
		&tAlarmOnZeroPower);

	// Guard.
	if (tRet != 4)
	{
		Prn::print(Prn::View21, "SuperStateACM::updateForT ERROR 102");
		return false;
	}

	// Copy temp variables to member variables. 
	mForwardPower_kw   = tForwardPower;
	mReflectedPower_kw = tReflectedPower;
	mAlarmFlag = tAlarmChar == 'A';
	mAlarmOnZeroPower = tAlarmOnZeroPower == 1;

	// Done.
	return true;
}
