/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "risSharedMemory.h"

#define  _SMSHARE_CPP_
#include "smShare.h"

namespace SM
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Shared memory object for the global instance.

Ris::SharedMemory gSharedMemory;

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize, there's no constructor. This is called by the process who
// first creates the shared memory.

void Share::initialize()
{
   mSuperStateACM.initialize();
   mSuperSettingsACM.initialize();

   mEventNotifyQueue.initialize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void Share::show(int aPF)
{
   Prn::print(aPF, "NumAttached      %d", gSharedMemory.getNumAttached());
}

void Share::show2()
{
   gSharedMemory.show();
}

void Share::showACM()
{
   mSuperStateACM.show();
   mSuperSettingsACM.show();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Create a shared memory region for the global instance and call placement
// new with the shared memory address. If this is the first process to access
// the region (it was created created, not opened) then initialize the global
// instance. Otherwise, do not initialize it, because the first process
// already did.

void initializeShare()
{
   // Create or open the shared memory.
   bool tFirstFlag = gSharedMemory.initialize("AAAASHARE3", 4096*32);

   // Create the global instance.
   gShare = new (gSharedMemory.mMemory) Share;

   // If this the first time that the shared memory was created then
   // initialize it.
   if (tFirstFlag)
   {
      printf("initialize\n");
      gShare->initialize();
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Close the shared memory region for the global instance.

void finalizeShare()
{
   // Finalize.
   gSharedMemory.finalize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
