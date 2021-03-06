#pragma once

/*==============================================================================
This file provides a set of variables that are used to define thread
priorities and processor number for threads in these programs.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risThreadsPriorities.h"

namespace Cmn
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class provides a set of variables that are used to define thread
// priorities and thread single processor numbers for threads in these
// programs.

class Priorities
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   Ris::Threads::Priority mTsPrint;
   Ris::Threads::Priority mSerialString;
   Ris::Threads::Priority mCommSeqLong;
   Ris::Threads::Priority mCommSeqShort;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   Priorities();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global singular instance.

#ifdef _CMNPRIORITIES_CPP_
          Priorities gPriorities;
#else
   extern Priorities gPriorities;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

