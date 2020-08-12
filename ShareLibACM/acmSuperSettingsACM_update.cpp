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

bool SuperSettingsACM::updateForLM(std::string* aResponse)
{
	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Extract some variables from the input response string.

	// >L=32768

	// Point to the first char in the response string. 
	// If it is a '>' then advance by one char to ignore it.
	const char* tBuffer = aResponse->c_str();
	if (tBuffer[0] == '>') tBuffer++;
	int tRet = 0;

	// Temp variables to be extracted from the response string.
	int   tV = 0;
	float tTxHighPowerThresh_pct = mTxHighPowerThresh_pct;
	float tRxHighPowerThresh_pct = 0.0;

	// 012345678901234
	// L=32768
	//
	// Guard.
	if ((tBuffer[0] != 'H') ||
		(tBuffer[1] != '=') ||
		(tBuffer[7] != 0)
		)
	{
		Prn::print(Prn::View21, "acmSuperStateACM::updateForLM ERROR 101");
		return false;
	}

	// Read from response string into temp variables.
	tRet = sscanf(tBuffer, "H=%d",
		&tV);

	// Guard.
	if (tRet != 1)
	{
		Prn::print(Prn::View21, "acmSuperStateACM::updateForLM ERROR 102");
		return false;
	}

	// Apply a mask.
	tV &= 0x7fff;

	// Convert.
	tRxHighPowerThresh_pct = 100.0 * tV / 26214.0;

	// Compare.
	if (my_closeto(tTxHighPowerThresh_pct, tRxHighPowerThresh_pct, 0.01))
	{
		// If ok then copy the temp to the member and set the
		// qx ack code for an ack. 
		mRxHighPowerThresh_pct = tRxHighPowerThresh_pct;
		mQxHighPowerThresh_pct = cQx_Ack;
	}
	else
	{
		// If not ok then set the qx ack code for a nak. 
		mQxHighPowerThresh_pct = cQx_Nak;
	}

	Prn::print(Prn::View21, "acmSuperStateACM::updateForLM %s %.2f",
		asString_Qx(mQxHighPowerThresh_pct), tRxHighPowerThresh_pct);

	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Done.

	return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Update some variables by decoding a received response string from a
// sent command. 

bool SuperSettingsACM::updateForN(std::string* aResponse)
{
	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Extract some variables from the input response string.

	// >H=32768

	// Point to the first char in the response string. 
	// If it is a '>' then advance by one char to ignore it.
	const char* tBuffer = aResponse->c_str();
	if (tBuffer[0] == '>') tBuffer++;
	int tRet = 0;

	// Temp variables to be extracted from the response string.
	int   tV = 0;
	bool tTxHighPowerAlarmEnable = mTxHighPowerAlarmEnable;
	bool tRxHighPowerAlarmEnable = false;

	// 012345678901234
	// L=32768
	//
	// Guard.
	if ((tBuffer[0] != 'H') ||
		(tBuffer[1] != '=') ||
		(tBuffer[7] != 0)
		)
	{
		Prn::print(Prn::View21, "acmSuperStateACM::updateForN ERROR 101");
		return false;
	}

	// Read from response string into temp variables.
	tRet = sscanf(tBuffer, "H=%d",
		&tV);

	// Guard.
	if (tRet != 1)
	{
		Prn::print(Prn::View21, "acmSuperStateACM::updateForN ERROR 102");
		return false;
	}

	// Convert.
	tRxHighPowerAlarmEnable = tV & 0x8000;

	// Compare.
	if (tTxHighPowerAlarmEnable == tRxHighPowerAlarmEnable)
	{
		// If ok then copy the temp to the member and set the
		// qx ack code for an ack. 
		mRxHighPowerAlarmEnable = tRxHighPowerAlarmEnable;
		mQxHighPowerAlarmEnable = cQx_Ack;
	}
	else
	{
		// If not ok then set the qx ack code for a nak. 
		mQxHighPowerAlarmEnable = cQx_Nak;
	}

	Prn::print(Prn::View21, "acmSuperStateACM::updateForN %s %s",
		asString_Qx(mQxHighPowerAlarmEnable), my_string_from_bool(tRxHighPowerAlarmEnable));

	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Done.

	return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Update some variables by decoding a received response string from a
// sent command. 

bool SuperSettingsACM::updateFor89(std::string* aResponse)
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
	int tV = 0;
	int tTxVSWRTrigger = mTxVSWRTrigger;
	int tRxVSWRTrigger = false;

	// 012345678901234
	// V=C
	//
	// Guard.
	if ((tBuffer[0] != 'V') ||
		(tBuffer[1] != '=') ||
		(tBuffer[3] != 0)
		)
	{
		Prn::print(Prn::View21, "acmSuperStateACM::updateFor89 ERROR 101");
		return false;
	}

	// Read from response string into temp variables.
	tRet = sscanf(tBuffer, "V=%x",
		&tV);

	// Guard.
	if (tRet != 1)
	{
		Prn::print(Prn::View21, "acmSuperStateACM::updateFor89 ERROR 102");
		return false;
	}

	// Convert.
	tRxVSWRTrigger = tV;

	// Compare.
	if (tTxVSWRTrigger == tRxVSWRTrigger)
	{
		// If ok then copy the temp to the member and set the
		// qx ack code for an ack. 
		mRxVSWRTrigger = tRxVSWRTrigger;
		mQxVSWRTrigger = cQx_Ack;
	}
	else
	{
		// If not ok then set the qx ack code for a nak. 
		mQxVSWRTrigger = cQx_Nak;
	}

	Prn::print(Prn::View21, "acmSuperStateACM::updateFor89 %s %d",
		asString_Qx(mQxVSWRTrigger), tRxVSWRTrigger);

	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Done.

	return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Update some variables by decoding a received response string from a
// sent command. 

bool SuperSettingsACM::updateFor6(std::string* aResponse)
{
	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Extract some variables from the input response string.

	// >H=32768

	// Point to the first char in the response string. 
	// If it is a '>' then advance by one char to ignore it.
	const char* tBuffer = aResponse->c_str();
	if (tBuffer[0] == '>') tBuffer++;
	int tRet = 0;

	// Temp variables to be extracted from the response string.
	int   tV = 0;
	bool tTxVSWRAlarmEnable = mTxVSWRAlarmEnable;
	bool tRxVSWRAlarmEnable = false;

	// 012345678901234
	// 000E
	// 0006
	
	// Guard.
	if (
		(tBuffer[4] != 0)
		)
	{
		Prn::print(Prn::View21, "acmSuperStateACM::updateFor6 ERROR 101");
		return false;
	}

	// Read from response string into temp variables.
	tRet = sscanf(tBuffer, "%x",
		&tV);

	// Guard.
	if (tRet != 1)
	{
		Prn::print(Prn::View21, "acmSuperStateACM::updateFor6 ERROR 102");
		return false;
	}

	// Convert.
	tRxVSWRAlarmEnable = tV & 0x0080;

	// Compare.
	if (tTxVSWRAlarmEnable == tRxVSWRAlarmEnable)
	{
		// If ok then copy the temp to the member and set the
		// qx ack code for an ack. 
		mRxVSWRAlarmEnable = tRxVSWRAlarmEnable;
		mQxVSWRAlarmEnable = cQx_Ack;
	}
	else
	{
		// If not ok then set the qx ack code for a nak. 
		mQxVSWRAlarmEnable = cQx_Nak;
	}

	Prn::print(Prn::View21, "acmSuperStateACM::updateFor6 %s %s",
		asString_Qx(mQxVSWRAlarmEnable), my_string_from_bool(tRxVSWRAlarmEnable));

	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Done.

	return true;
}

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
