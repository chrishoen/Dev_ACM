#pragma once

/*==============================================================================
acm common definitions.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constants.

// Operating modes.
static const int cQx_None = 0;
static const int cQx_Request = 1;
static const int cQx_Pending1 = 2;
static const int cQx_Pending2 = 3;
static const int cQx_Ack = 4;
static const int cQx_Nak = 5;

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Methods.

// Return a variable as a string.
const char* asString_Qx(int aOpMode);


//******************************************************************************
//******************************************************************************
//******************************************************************************

