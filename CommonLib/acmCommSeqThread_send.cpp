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
// Send super settings function. This is bound to the qcall. Polls the
// super settings and for any settings variable that has pending1, send 
// a corresponding command to the acm to set the variable and then send 
// a command to read the variable as verification.

void CommSeqThread::executeSendSettings()
{
   Prn::print(Prn::View11, "CommSeqThread::executeSend BEGIN");

   // Initialize the synchronization objects.
   mAcquireWaitable.initialize(Cmn::gProgramParms.mDelay);
   mNotify.clearFlags();

   try
   {
   }
   catch(int aException)
   {
      Prn::print(0, "EXCEPTION CommSeqThread::executeSendSettings %d %s", aException, mNotify.mException);
   }

   // Finalize the synchronization objects.
   mAcquireWaitable.finalize();
   mNotify.clearFlags();

   Prn::print(Prn::View11, "CommSeqThread::executeSendSettings END");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace