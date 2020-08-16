#pragma once

/*==============================================================================
Shared memory region.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risSRSWStringQueue.h"

#include "acmSuperStateACM.h"
#include "acmSuperSettingsACM.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SM
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// The following rules are for shared memory regions that are shared between
// different processes (who therefore have different address spaces):
// 
// 1) No constructors.
// 2) No pointers.
// 3) No dynamic memory, this means no std::string, no std::vector, ...
// 4) No class inheritance (no vtables).
//
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class implements a set of variables that live in a shared memory
// region that is concurrently accessed by cproc, touchscreen, and web gui
// code.

class Share
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Super state variables.
   ACM::SuperStateACM mSuperStateACM;
   ACM::SuperSettingsACM mSuperSettingsACM;

   // Event notification queue.
   Ris::SRSWStringQueue<200, 100> mEventNotifyQueue;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Initialize, there's no constructor. This is called by the process who
   // first creates the shared memory.
   void initialize();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   void show(int aPrintFilter = 0);
   void show2();
   void showACM();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance initialize and finalize.

// Create a shared memory region for the global instance and call placement
// new with the shared memory address. If this is the first process to access
// the region (it was created created, not opened) then initialize the global
// instance. Otherwise, do not initialize it, because the first process
// already did.
void initializeShare();

// Close the shared memory region for the global instance.
void finalizeShare();

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance.

#ifdef _SMSHARE_CPP_
          Share* gShare = 0;
#else
   extern Share* gShare;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

