//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "acmSuperDefs.h"


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a super state variable as a string.

char* get_Qx_asString(int aOpMode)
{
   switch (aOpMode)
   {
   case cQx_None: return "None";
   case cQx_Request: return "Request";
   case cQx_Pending: return "Pending";
   case cQx_Ack: return "Ack";
   case cQx_Nak: return "Nak";
   }
   return "UNKNOWN";
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
