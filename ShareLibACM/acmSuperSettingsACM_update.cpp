//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "acmSuperDefs.h"
#include "acmSuperSettingsACM.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace ACM
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Update some variables by decoding a received response string from a
// sent command. 

bool SuperSettingsACM::updateForJK(std::string* aResponse)
{
	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Extract some variables from the input response string.

	// >V=C

	// Point to the first char in the response string. 
	// If it is a '>' then advance by one char to ignore it.
	const char* tBuffer = aResponse->c_str();
	if (tBuffer[0] == '>') tBuffer++;
	int tRet = 0;

	// Temp variables to be extracted from the response string.
	int tV1 = 0;
	int tV2 = 0;
	int tTxForwardGain = mTxForwardGain;
	int tTxReverseGain = mTxReverseGain;
	int tRxForwardGain = 0;
	int tRxReverseGain = 0;

	// 01234567JK01234
	// G=88
	//
	// Guard.
	if ((tBuffer[0] != 'G') ||
		(tBuffer[1] != '=') ||
		(tBuffer[4] != 0)
		)
	{
		Prn::print(Prn::View21, "acmSuperStateACM::updateForJK ERROR 101");
		return false;
	}

	// Read from response string into temp variables.
	tRet = sscanf(tBuffer, "G=%1d%1d",
		&tV1, &tV2);

	// Guard.
	if (tRet != 2)
	{
		Prn::print(Prn::View21, "acmSuperStateACM::updateForJK ERROR 102");
		return false;
	}

	// Convert.
	tRxForwardGain = tV1;
	tRxReverseGain = tV2;

	// Compare.
	if (tRxForwardGain == tTxForwardGain && tRxReverseGain == tTxReverseGain)
	{
		// If ok then copy the temp to the member and set the
		// qx ack code for an ack. 
		mRxForwardGain = tRxForwardGain;
		mRxReverseGain = tRxReverseGain;
		mQxGain = cQx_Ack;
	}
	else
	{
		// If not ok then set the qx ack code for a nak. 
		mQxVSWRTrigger = cQx_Nak;
	}

	Prn::print(Prn::View21, "acmSuperStateACM::updateForJK %s %1d %1d",
		asString_Qx(mQxGain), tRxForwardGain, tRxReverseGain);

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
