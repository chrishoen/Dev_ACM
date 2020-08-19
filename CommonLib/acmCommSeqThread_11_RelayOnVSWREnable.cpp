/*==============================================================================
Detestion:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "cmnProgramParms.h"
#include "smShare.h"
#include "acmCommSeqThread.h"

namespace ACM
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// For the individual settings variable, process the super settings
// as follows:
//
// If the tx flag is true then then send a command to the acm to set the
// variable, based on the tx variable. Receive and process the response
// to set the rx and qx variables. 
//
// If the tx flag is false then send a command to the acm to read the
// current variable. Receive and process the response to set the rx
// variable.

void CommSeqThread::txrxRelayOnVSWREnable(bool aTxFlag)
{
	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Send a command to the acm.

	// Do this first.
	ACM::SuperSettingsACM* tS = &SM::gShare->mSuperSettingsACM;
	ACM::SuperStateACM* tX = &SM::gShare->mSuperStateACM;
	tS->mQxRelayOnVSWREnable = cQx_Pending2;

	// This one's a disaster.
	Prn::print(Prn::View21, "RelayOnVSWREnable           Nak IGNORED");
	tS->mQxRelayOnVSWREnable = cQx_Nak;
	return;
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace