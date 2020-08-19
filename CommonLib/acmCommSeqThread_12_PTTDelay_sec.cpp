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


//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace