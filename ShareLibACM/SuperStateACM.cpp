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
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void SuperStateACM::show(int aPF)
{
	Prn::print(aPF, "mForwardPower_kw      %10.2f", mForwardPower_kw);
   Prn::print(aPF, "mForwardPower_dbm     %10.2f", mForwardPower_dbm);
	Prn::print(aPF, "mReflectedPower_kw    %10.2f", mReflectedPower_kw);
   Prn::print(aPF, "mReflectedPower_dbm   %10.2f", mReflectedPower_dbm);
	Prn::print(aPF, "mVSWR                 %10.2f", mVSWR);
	Prn::print(aPF, "mReturnLoss_db        %10.2f", mReturnLoss_db);
	Prn::print(aPF, "mRho                  %10.2f", mRho);
	Prn::print(aPF, "mEfficiency_percent   %10.2f", mEfficiency_percent);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Update some variables by decoding a received response string from a
// sent command. 

bool SuperStateACM::updateForT(std::string* aResponse)
{
	// 012345678901234
	// >000.0,00.00 0
	const char* tResponse = aResponse->c_str();
	char tTemp[10];

	// Guard.
	if (tResponse[0]  != '>') return false;
	if (tResponse[4]  != '.') return false;
	if (tResponse[6]  != ',') return false;
	if (tResponse[6]  != ' ') return false;
	if (tResponse[14] != 0)   return false;

	// Decode.
	tTemp[0] = tResponse[1];
	tTemp[1] = tResponse[2];
	tTemp[2] = tResponse[3];
	tTemp[3] = tResponse[4];
	tTemp[4] = tResponse[5];
	tTemp[5] = 0;
	mForwardPower_kw = atof(tTemp);;
}

