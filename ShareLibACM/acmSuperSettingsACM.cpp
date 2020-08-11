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
// Initialize.

void SuperSettingsACM::initialize()
{
	// Low power threshold.
	mTxLowPowerThresh_pct = 0.0;
	mRxLowPowerThresh_pct = 0.0;
	mQxLowPowerThresh_pct = 0;

	// Low power alarm.
	mTxLowPowerAlarmEnable = false;
	mRxLowPowerAlarmEnable = false;
	mQxLowPowerAlarmEnable = 0;

	// High power threshold.
	mTxHighPowerThresh_pct = 0.0;
	mRxHighPowerThresh_pct = 0.0;
	mQxHighPowerThresh_pct = 0;

	// High power alarm.
	mTxHighPowerAlarmEnable = false;
	mRxHighPowerAlarmEnable = false;
	mQxHighPowerAlarmEnable = 0;

	// VSWR trigger.
	mTxVSWRTrigger = 0;
	mRxVSWRTrigger = 0;
	mQxVSWRTrigger = 0;

	// VSWR alarm.
	mTxVSWRAlarmEnable = false;
	mRxVSWRAlarmEnable = false;
	mQxVSWRAlarmEnable = 0;

	// Gain.
	mTxForwardGain = 0;
	mTxReverseGain = 0;
	mRxForwardGain = 0;
	mRxReverseGain = 0;
	mQxGain = 0;

	// Latch alarm enable.
	mTxLatchAlarmEnable = false;
	mRxLatchAlarmEnable = false;
	mQxLatchAlarmEnable = 0;

	// Power up alarm enable.
	mTxPowerUpAlarmEnable = false;
	mRxPowerUpAlarmEnable = false;
	mQxPowerUpAlarmEnable = 0;

	// Relay energize on power alarm enable.
	mTxRelayOnPowerEnable = false;
	mRxRelayOnPowerEnable = false;
	mQxRelayOnPowerEnable = 0;

	// Relay energize on VSWR alarm enable.
	mTxRelayOnVSWREnable = false;
	mRxRelayOnVSWREnable = false;
	mQxRelayOnVSWREnable = 0;

	// Check VSWR on zero power.
	mTxCheckVSWROnZeroEnable = false;
	mRxCheckVSWROnZeroEnable = false;
	mQxCheckVSWROnZeroEnable = 0;

	// PTT delay.
	mTxPTTDelay_sec = 0.0;
	mRxPTTDelay_sec = 0.0;
	mQxPTTDelay_sec = 0;

	// PTT alarm.
	mTxPTTAlarmEnable = false;
	mRxPTTAlarmEnable = false;
	mQxPTTAlarmEnable = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void SuperSettingsACM::show(int aPF)
{
	// Low power threshold.
	Prn::print(aPF, "LowPowerThresh_pct           %10.2f %10.2f %10s",
	   mTxLowPowerThresh_pct,
	   mRxLowPowerThresh_pct,
		asString_Qx(mQxLowPowerThresh_pct));

	// Low power alarm.
	Prn::print(aPF, "LowPowerAlarmEnable          %10s %10s %10s",
		my_string_from_bool(mTxLowPowerAlarmEnable),
		my_string_from_bool(mRxLowPowerAlarmEnable),
		asString_Qx(mQxLowPowerAlarmEnable));

	// High power threshold.
	Prn::print(aPF, "HighPowerThresh_pct          %10.2f %10.2f %10s",
		mTxHighPowerThresh_pct,
		mRxHighPowerThresh_pct,
		asString_Qx(mQxHighPowerThresh_pct));

	// High power alarm.
	Prn::print(aPF, "HighPowerAlarmEnable         %10s %10s %10s",
		my_string_from_bool(mTxHighPowerAlarmEnable),
		my_string_from_bool(mRxHighPowerAlarmEnable),
	   asString_Qx(mQxHighPowerAlarmEnable));

	// VSWR trigger.
	Prn::print(aPF, "VSWRTrigger                  %10d %10d %10s",
		mTxVSWRTrigger,
		mRxVSWRTrigger,
		asString_Qx(mQxVSWRTrigger));

	// VSWR alarm.
	Prn::print(aPF, "VSWRAlarmEnable              %10s %10s %10s",
		my_string_from_bool(mTxVSWRAlarmEnable),
		my_string_from_bool(mRxVSWRAlarmEnable),
		asString_Qx(mQxVSWRAlarmEnable));

	// Gain.
	Prn::print(aPF, "Gain                         %8d %1d %8d %1d %10s",
		mTxForwardGain,
		mTxReverseGain,
		mRxForwardGain,
		mRxReverseGain,
		asString_Qx(mQxGain));

	// Latch alarm enable.
	Prn::print(aPF, "LatchAlarmEnable             %10s %10s %10s",
		my_string_from_bool(mTxLatchAlarmEnable),
		my_string_from_bool(mRxLatchAlarmEnable),
		asString_Qx(mQxLatchAlarmEnable));

	// Power up alarm enable.
	Prn::print(aPF, "PowerUpAlarmEnable           %10s %10s %10s",
		my_string_from_bool(mTxPowerUpAlarmEnable),
		my_string_from_bool(mRxPowerUpAlarmEnable),
		asString_Qx(mQxPowerUpAlarmEnable));

	// Relay energize on power alarm enable.
	Prn::print(aPF, "RelayOnPowerAlarmEnable      %10s %10s %10s",
		my_string_from_bool(mTxRelayOnPowerEnable),
		my_string_from_bool(mRxRelayOnPowerEnable),
		asString_Qx(mQxRelayOnPowerEnable));

	// Relay energize on VSWR alarm enable.
	Prn::print(aPF, "RelayOnVSWRAlarmEnable       %10s %10s %10s",
		my_string_from_bool(mTxRelayOnVSWREnable),
		my_string_from_bool(mRxRelayOnVSWREnable),
		asString_Qx(mQxRelayOnVSWREnable));

	// Check VSWR on zero power.
	Prn::print(aPF, "CheckVSWROnZeroPowerEnable   %10s %10s %10s",
		my_string_from_bool(mTxCheckVSWROnZeroEnable),
		my_string_from_bool(mRxCheckVSWROnZeroEnable),
		asString_Qx(mQxCheckVSWROnZeroEnable));

	// PTT delay.
	Prn::print(aPF, "PTTDelay_sec                 %10.2f %10.2f %10s",
		mTxPTTDelay_sec,
		mRxPTTDelay_sec,
		asString_Qx(mQxPTTDelay_sec));

	// PTT alarm.
	// Power up alarm enable.
	Prn::print(aPF, "PTTAlarmEnable               %10s %10s %10s",
		my_string_from_bool(mTxPTTAlarmEnable),
		my_string_from_bool(mRxPTTAlarmEnable),
		asString_Qx(mQxPTTAlarmEnable));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Request the setting of settings variables. 

void SuperSettingsACM::requestLowPowerThresh_pct(float aValue)
{
	mTxLowPowerThresh_pct = aValue;
	mQxLowPowerThresh_pct = cQx_Request;
}
void SuperSettingsACM::requestLowPowerAlarmEnable(bool aValue)
{
	mTxLowPowerAlarmEnable = aValue;
	mQxLowPowerAlarmEnable = cQx_Request;
}
void SuperSettingsACM::requestHighPowerThresh_pct(float aValue)
{
	mTxHighPowerThresh_pct = aValue;
	mQxHighPowerThresh_pct = cQx_Request;
}
void SuperSettingsACM::requestHighPowerAlarmEnable(bool aValue)
{
	mTxHighPowerAlarmEnable = aValue;
	mQxHighPowerAlarmEnable = cQx_Request;
}
void SuperSettingsACM::requestGain(int aForward, int aReverse)
{
	mTxForwardGain = aForward;
	mTxReverseGain = aReverse;
	mQxGain = cQx_Request;
}
void SuperSettingsACM::requestLatchAlarmEnable(bool aValue)
{
	mTxLatchAlarmEnable = aValue;
	mQxLatchAlarmEnable = cQx_Request;
}
void SuperSettingsACM::requestPowerUpAlarmEnable(bool aValue)
{
	mTxPowerUpAlarmEnable = aValue;
	mQxPowerUpAlarmEnable = cQx_Request;
}
void SuperSettingsACM::requestRelayOnPowerEnable(bool aValue)
{
	mTxRelayOnPowerEnable = aValue;
	mQxRelayOnPowerEnable = cQx_Request;
}
void SuperSettingsACM::requestRelayOnVSWREnable(bool aValue)
{
	mTxRelayOnVSWREnable = aValue;
	mQxRelayOnVSWREnable = cQx_Request;
}
void SuperSettingsACM::requestCheckVSWROnZeroEnable(bool aValue)
{
	mTxCheckVSWROnZeroEnable = aValue;
	mQxCheckVSWROnZeroEnable = cQx_Request;
}
void SuperSettingsACM::requestPTTDelay_sec(float aValue)
{
	mTxPTTDelay_sec = aValue;
	mQxPTTDelay_sec = cQx_Request;
}
void SuperSettingsACM::requestPTTAlarmEnable(bool aValue)
{
	mTxPTTAlarmEnable = aValue;
	mQxPTTAlarmEnable = cQx_Request;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Update some variables by decoding a received response string from a
// sent command. 

bool SuperSettingsACM::updateForDE(std::string* aResponse)
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
	float tTxLowPowerThresh_pct = mTxLowPowerThresh_pct;
	float tRxLowPowerThresh_pct = 0.0;

	// 012345678901234
	// L=32768
	//
	// Guard.
	if ((tBuffer[0] != 'L') ||
		(tBuffer[1] != '=') ||
		(tBuffer[7] != 0)
		)
	{
		Prn::print(Prn::View21, "acmSuperStateACM::updateForDE ERROR 101");
		return false;
	}

	// Read from response string into temp variables.
	tRet = sscanf(tBuffer, "L=%d",
		&tV);

	// Guard.
	if (tRet != 1)
	{
		Prn::print(Prn::View21, "acmSuperStateACM::updateForDE ERROR 102");
		return false;
	}

	// Apply a mask.
	tV &= 0x7fff;

	// Convert.
	tRxLowPowerThresh_pct = 100.0 * tV / 26214.0;

	// Compare.
	if (my_closeto(tTxLowPowerThresh_pct, tRxLowPowerThresh_pct, 0.01))
	{
		// If ok then copy the temp to the member and set the
	   // qx ack code for an ack. 
		mRxLowPowerThresh_pct = tRxLowPowerThresh_pct;
		mQxLowPowerThresh_pct = cQx_Ack;
	}
	else
	{
		// If not ok then set the qx ack code for a nak. 
		mQxLowPowerThresh_pct = cQx_Nak;
	}

	Prn::print(Prn::View21, "acmSuperStateACM::updateForDE %s %.2f", 
		asString_Qx(mQxLowPowerThresh_pct), tRxLowPowerThresh_pct);

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

bool SuperSettingsACM::updateForG(std::string* aResponse)
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
	bool tTxLowPowerAlarmEnable = mTxLowPowerAlarmEnable;
	bool tRxLowPowerAlarmEnable = false;

	// 012345678901234
	// L=32768
	//
	// Guard.
	if ((tBuffer[0] != 'L') ||
		(tBuffer[1] != '=') ||
		(tBuffer[7] != 0)
		)
	{
		Prn::print(Prn::View21, "acmSuperStateACM::updateForG ERROR 101");
		return false;
	}

	// Read from response string into temp variables.
	tRet = sscanf(tBuffer, "L=%d",
		&tV);

	// Guard.
	if (tRet != 1)
	{
		Prn::print(Prn::View21, "acmSuperStateACM::updateForG ERROR 102");
		return false;
	}

	// Convert.
	tRxLowPowerAlarmEnable = tV & 0x8000;

	// Compare.
	if (tTxLowPowerAlarmEnable == tRxLowPowerAlarmEnable)
	{
		// If ok then copy the temp to the member and set the
		// qx ack code for an ack. 
		mRxLowPowerAlarmEnable = tRxLowPowerAlarmEnable;
		mQxLowPowerAlarmEnable = cQx_Ack;
	}
	else
	{
		// If not ok then set the qx ack code for a nak. 
		mQxLowPowerAlarmEnable = cQx_Nak;
	}

	Prn::print(Prn::View21, "acmSuperStateACM::updateForG %s %s",
		asString_Qx(mQxLowPowerAlarmEnable), my_string_from_bool(tRxLowPowerAlarmEnable));

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
} //namespace
