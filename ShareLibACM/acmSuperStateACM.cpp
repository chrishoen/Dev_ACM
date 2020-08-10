//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "acmSuperStateACM.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace ACM
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize.

void SuperStateACM::initialize()
{
	mForwardPower_kw = 0.0;
	mReflectedPower_kw = 0.0;
	mVSWR = 0.0;
	mReturnLoss_db = 0.0;
	mRho = 0.0;
	mEfficiency_pct = 0.0;

	mAlarmFlag = false;
	mAlarmOnZeroPower = false;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void SuperStateACM::show(int aPF)
{
	Prn::print(aPF, "ForwardPower_kw      %10.3f", mForwardPower_kw);
	Prn::print(aPF, "ReflectedPower_kw    %10.3f", mReflectedPower_kw);
	Prn::print(aPF, "VSWR                 %10.2f", mVSWR);
	Prn::print(aPF, "ReturnLoss_db        %10.2f", mReturnLoss_db);
	Prn::print(aPF, "Rho                  %10.2f", mRho);
	Prn::print(aPF, "Efficiency_pct       %10.2f", mEfficiency_pct);
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
	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Extract some variables from the input response string.

	// >000.0,00.00A1
	// 012345678901234
	// 000.0,00.00A1

	// Point to the first char in the response string. 
	// If it is a '>' then advance by one char to ignore it.
	const char* tBuffer = aResponse->c_str();
	if (tBuffer[0] == '>') tBuffer++;

	// Temp variables to be extracted from the response string.
	float tForwardPower_w = -1;
	float tReflectedPower_w = -1;
	char  tAlarmChar = 'z';
	int   tAlarmOnZeroPower = 9;
	int   tRet = 0;

	// 012345678901234
	// 000.0,00.00A1
	//
	// Guard.
	if ((tBuffer[3] != '.') ||
		(tBuffer[5] != ',') ||
		(tBuffer[13] != 0)
		)
	{
		Prn::print(Prn::View21, "acmSuperStateACM::updateForT ERROR 101");
		return false;
	}

	// Read from response string into temp variables.
	tRet = sscanf(tBuffer, "%f,%f%c%d",
		&tForwardPower_w,
		&tReflectedPower_w,
		&tAlarmChar,
		&tAlarmOnZeroPower);

	// Guard.
	if (tRet != 4)
	{
		Prn::print(Prn::View21, "acmSuperStateACM::updateForT ERROR 102");
		return false;
	}

	// Copy temp variables to member variables. 
	mForwardPower_kw = tForwardPower_w;
	mReflectedPower_kw = tReflectedPower_w;
	mAlarmFlag = tAlarmChar == 'A';
	mAlarmOnZeroPower = tAlarmOnZeroPower == 1;

	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Calculate some more variables from the extracted variables.

	// Guard.
	if (my_closeto(tForwardPower_w, 0.0, 0.000001))
	{
		// ff zero then error
		Prn::print(Prn::View21, "acmSuperStateACM::updateForT ERROR 201");
		return false;
	}

	// Guard.
	if (tForwardPower_w <= tReflectedPower_w)
	{
		Prn::print(Prn::View21, "acmSuperStateACM::updateForT ERROR 202");
		return false;
	}

	// Calculate some member variables.
	mForwardPower_kw = tForwardPower_w / 1000.0;
	mReflectedPower_kw = tReflectedPower_w / 1000.0;

	// Calculate some member variables.
	float tGamma = sqrt(tReflectedPower_w / tForwardPower_w);
	mVSWR = (1.0 + tGamma) / (1.0 - tGamma);
	mReturnLoss_db = -20.0 * log(tGamma);
	mRho = tGamma;
	mEfficiency_pct = (tForwardPower_w - tReflectedPower_w) / tForwardPower_w;

	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Done.

	return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
} //namespace

