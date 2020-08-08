//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"
#include "my_functions.h"

#include "risCmdLineFile.h"

#define  _CMNPROGRAMPARMS_CPP_
#include "cmnProgramParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Cmn
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

ProgramParms::ProgramParms()
{
   reset();
}

void ProgramParms::reset()
{
   BaseClass::reset();
   BaseClass::setFilePath_RelativeToBaseDir("files/ProgramParms.txt");

   mCmdCommPortDevice[0] = 0;
   mCmdCommPortSetup[0] = 0;
   mCmdCommPortTimeout = 0;
   mCmdCommPort485Flag = false;
   mDelay = 0;
   mTxCommand[0] = 0;

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void ProgramParms::show()
{
   char tBuffer[40];
   printf("\n");
   printf("ProgramParms******************************************* %s\n", mTargetSection);

   printf("\n");
   printf("CmdCommPortDevice       %-12s\n", mCmdCommPortDevice);
   printf("CmdCommPortSetup        %-12s\n", mCmdCommPortSetup);
   printf("CmdCommPortTimeout      %12d\n",  mCmdCommPortTimeout);
   printf("CmdCommPort485Flag      %12s\n",  my_string_from_bool(mCmdCommPort485Flag));

   printf("\n");
   printf("SerialStringPrintLevel  %12s\n",  mSerialStringPrintLevel.asString(tBuffer));
   printf("TestSeqShortPrintLevel  %12s\n",  mTestSeqShortPrintLevel.asString(tBuffer));
   printf("TestSeqLongPrintLevel   %12s\n",  mTestSeqLongPrintLevel.asString(tBuffer));

   printf("\n");
   printf("Delay                   %12d\n", mDelay);
   printf("TxCommand               %12s\n", mTxCommand);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void ProgramParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if (aCmd->isCmd("CmdCommPortDevice"))      aCmd->copyArgString(1, mCmdCommPortDevice, cMaxStringSize);
   if (aCmd->isCmd("CmdCommPortSetup"))       aCmd->copyArgString(1, mCmdCommPortSetup, cMaxStringSize);
   if (aCmd->isCmd("CmdCommPortTimeout"))     mCmdCommPortTimeout = aCmd->argInt(1);
   if (aCmd->isCmd("CmdCommPort485Flag"))     mCmdCommPort485Flag = aCmd->argBool(1);

   if (aCmd->isCmd("SerialStringPrintLevel")) mSerialStringPrintLevel.readArgs(aCmd);
   if (aCmd->isCmd("TestSeqShortPrintLevel")) mTestSeqShortPrintLevel.readArgs(aCmd);
   if (aCmd->isCmd("TestSeqLongPrintLevel"))  mTestSeqLongPrintLevel.readArgs(aCmd);

   if (aCmd->isCmd("Delay"))                  mDelay = aCmd->argInt(1);
   if (aCmd->isCmd("TxCommand"))              aCmd->copyArgString(1, mTxCommand, cMaxStringSize);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate expanded member variables. This is called after the entire
// section of the command file has been processed.

void ProgramParms::expand()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace