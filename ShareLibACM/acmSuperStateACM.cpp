//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "json.h"
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
	mForwardPower_dbm = -666.0;
	mReflectedPower_dbm = -666.0;
	mVSWR = 0.0;
	mReturnLoss_db = 0.0;
	mRho = 0.0;
	mEfficiency_pct = 0.0;

	mAlarmFlag = false;
	mAlarmOnZeroPower = false;

	mCheckVSWROnZeroEnable = false;
	mHighPowerAlarmEnable = false;
	mRelayOnVSWREnable = false;
	mVSWRAlarmEnable = false;
	mLowPowerAlarmEnable = false;
	mLatchAlarmEnable = false;
	mPowerUpAlarmEnable = false;
	mPTTEnable = false;
	mRelayOnPowerEnable = false;

	mOverrideForwardPower_w = 0.0;
	mOverrideReflectedPower_w = 0.0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void SuperStateACM::show(int aPF)
{
	Prn::print(aPF, "ForwardPower_kw            %10.6f", mForwardPower_kw);
	Prn::print(aPF, "ReflectedPower_kw          %10.6f", mReflectedPower_kw);
	Prn::print(aPF, "ForwardPower_dbm           %10.1f", mForwardPower_dbm);
	Prn::print(aPF, "ReflectedPower_dbm         %10.1f", mReflectedPower_dbm);
	Prn::print(aPF, "VSWR                       %10.2f", mVSWR);
	Prn::print(aPF, "ReturnLoss_db              %10.2f", mReturnLoss_db);
	Prn::print(aPF, "Rho                        %10.2f", mRho);
	Prn::print(aPF, "Efficiency_pct             %10.2f", mEfficiency_pct);
	Prn::print(aPF, "AlarmFlag                  %10s", my_string_from_bool(mAlarmFlag));
	Prn::print(aPF, "AlarmOnZeroPower           %10s", my_string_from_bool(mAlarmOnZeroPower));

	Prn::print(aPF, "");
	Prn::print(aPF, "OverrideForwardPower_w     %10.3f", mOverrideForwardPower_w);
	Prn::print(aPF, "OverrideReflectedPower_w   %10.3f", mOverrideReflectedPower_w);

	Prn::print(aPF, "");
	Prn::print(aPF, "CheckVSWROnZeroEnable      %10s", my_string_from_bool(mCheckVSWROnZeroEnable));
	Prn::print(aPF, "HighPowerAlarmEnable       %10s", my_string_from_bool(mHighPowerAlarmEnable));
	Prn::print(aPF, "RelayOnVSWREnable          %10s", my_string_from_bool(mRelayOnVSWREnable));
	Prn::print(aPF, "VSWRAlarmEnable            %10s", my_string_from_bool(mVSWRAlarmEnable));
	Prn::print(aPF, "LowPowerAlarmEnable        %10s", my_string_from_bool(mLowPowerAlarmEnable));
	Prn::print(aPF, "LatchAlarmEnable           %10s", my_string_from_bool(mLatchAlarmEnable));
	Prn::print(aPF, "PowerUpAlarmEnable         %10s", my_string_from_bool(mPowerUpAlarmEnable));
	Prn::print(aPF, "PTTEnable                  %10s", my_string_from_bool(mPTTEnable));
	Prn::print(aPF, "RelayOnPowerEnable         %10s", my_string_from_bool(mRelayOnPowerEnable));
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

	// If the overrides are not zero then override the inputs.
	if (mOverrideForwardPower_w != 0.0)
	{
		tForwardPower_w = mOverrideForwardPower_w;
		tReflectedPower_w = mOverrideReflectedPower_w;
	}

	// Copy temp variables to member variables. 
	mForwardPower_kw = tForwardPower_w / 1000.0;
	mReflectedPower_kw = tReflectedPower_w / 1000.0;
	mForwardPower_dbm = 10.0 * log10(tForwardPower_w * 1000.0);
	mReflectedPower_dbm = 10.0 * log10(tReflectedPower_w * 1000.0);
	mAlarmFlag = tAlarmChar == 'A';
	mAlarmOnZeroPower = tAlarmOnZeroPower == 1;

	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Calculate some more variables from the extracted variables.

	// Guard.
	if (my_iscloseto(tForwardPower_w, 0.0, 0.00001))
	{
		// ff zero then error
		//Prn::print(Prn::View21, "acmSuperStateACM::updateForT ERROR 201");
		return false;
	}

	// Guard.
	if (tForwardPower_w <= tReflectedPower_w)
	{
		//Prn::print(Prn::View21, "acmSuperStateACM::updateForT ERROR 202");
		return false;
	}

	// Calculate some member variables.
	mForwardPower_kw = tForwardPower_w / 1000.0;
	mReflectedPower_kw = tReflectedPower_w / 1000.0;

	// Calculate some member variables.
	float tGamma = sqrt(tReflectedPower_w / tForwardPower_w);
	mVSWR = (1.0 + tGamma) / (1.0 - tGamma);
	mReturnLoss_db = -20.0 * log10(tGamma);
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
// Update flag variables.

void SuperStateACM::updateFlags(int aFlags)
{
	mCheckVSWROnZeroEnable = aFlags & 0x0001;
	mHighPowerAlarmEnable  = aFlags & 0x0002;
	mRelayOnVSWREnable     = aFlags & 0x0004;
	mVSWRAlarmEnable       = aFlags & 0x0008;
	mLowPowerAlarmEnable   = aFlags & 0x0020;
	mLatchAlarmEnable      = aFlags & 0x0040;
	mPowerUpAlarmEnable    = aFlags & 0x0080;
	mPTTEnable             = aFlags & 0x0100;
	mRelayOnPowerEnable    = aFlags & 0x0200;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return the super state encoded into a json string.

std::string SuperStateACM::asJsonString()
{
	Json::Value tValue;

	tValue["ForwardPower_kw"] = mForwardPower_kw;
	tValue["ReflectedPower_kw"] = mReflectedPower_kw;
	tValue["ForwardPower_dbm"] = mForwardPower_dbm;
	tValue["ReflectedPower_dbm"] = mReflectedPower_dbm;
	tValue["VSWR"] = mVSWR;
	tValue["ReturnLoss_db"] = mReturnLoss_db;
	tValue["Rho"] = mRho;
	tValue["Efficiency_pct"] = mEfficiency_pct;
	tValue["AlarmFlag"] = mAlarmFlag;
	tValue["AlarmOnZeroPower"] = mAlarmOnZeroPower;

	std::string tString;
	Json::FastWriter tWriter;
	tString = tWriter.write(tValue);
	return tString;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
} //namespace

#if 0

ForwardPower_kw ForwardPower_kw
ReflectedPower_kw ReflectedPower_kw
ForwardPower_dbm ForwardPower_dbm
ReflectedPower_dbm ReflectedPower_dbm
VSWR VSWR
ReturnLoss_db ReturnLoss_db
Rho Rho
Efficiency_pct Efficiency_pct
AlarmFlag AlarmFlag
AlarmOnZeroPower AlarmOnZeroPower

#endif