#include "stdafx.h"

#include "risThreadsProcess.h"

#include "cmnProgramParms.h"
#include "smShare.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize program resources.

void main_initialize(int argc,char** argv)
{
   printf("acmproc Program********************************************BEGIN\n");
   printf("acmproc Program********************************************BEGIN\n");
   printf("acmproc Program********************************************BEGIN\n\n");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Enter process.

   // Set program process for high priority.
   Ris::Threads::enterProcessHigh();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize.

   // Read parameters files.
   Cmn::gProgramParms.reset();
   Cmn::gProgramParms.readSection("default");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize thread services.

   TS::reset();
   TS::setProgramName("cprint");
   TS::setProgramPrintLevel(TS::PrintLevel(0, 0));
   TS::initialize();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize print facility.

   // Initialize print.
   Prn::resetPrint(Cmn::gProgramParms.mPrintViewIPAddress);
   Prn::useConsole(1);
   Prn::useConsole(2);
   Prn::initializePrint();

   // Initialize print filters.
   Prn::setFilter(Prn::View11, true,  1);
   Prn::setFilter(Prn::View12, false, 1);
   Prn::setFilter(Prn::View13, false, 1);
   Prn::setFilter(Prn::View14, false, 1);

   Prn::setFilter(Prn::View21, true,  2);
   Prn::setFilter(Prn::View22, false, 2);
   Prn::setFilter(Prn::View23, false, 2);
   Prn::setFilter(Prn::View24, false, 2);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize.

   // Initialize shared memory.
   SM::initializeShare();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finalize program resourcs.

void main_finalize()
{
   // Finalize shared memory.
   SM::finalizeShare();

   // Finalize print facility.
   Prn::finalizePrint();

   // Done.
   printf("\n");
   printf("acmproc Program********************************************END\n\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
