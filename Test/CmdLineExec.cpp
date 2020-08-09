#include "stdafx.h"

#include "CmdLineExec.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

CmdLineExec::CmdLineExec()
{
}

void CmdLineExec::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class is the program command line executive. It processes user
// command line inputs and executes them. It inherits from the command line
// command executive base class, which provides an interface for executing
// command line commands. It provides an override execute function that is
// called by a console executive when it receives a console command line input.
// The execute function then executes the command.

void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if(aCmd->isCmd("RESET"  ))  reset();
   if(aCmd->isCmd("GO1"    ))  executeGo1(aCmd);
   if(aCmd->isCmd("GO2"    ))  executeGo2(aCmd);
   if(aCmd->isCmd("GO3"    ))  executeGo3(aCmd);
   if(aCmd->isCmd("GO4"    ))  executeGo4(aCmd);
   if(aCmd->isCmd("GO5"    ))  executeGo5(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   char tBuffer[64];
   strcpy(tBuffer, ">000.0,00.00 0");
   strcpy(tBuffer, "123.4,12.34,2");
   strcpy(tBuffer, ">123.4,12.34A1");
   float tForwardPower = -1;
   float tReflectedPower = -1;
   char  tAlarmCode = 'z';
   int   tAlarmOnZeroPower =  9;
   int tRet = 0;

   tRet = sscanf(tBuffer, ">%f,%f%c%d",
      &tForwardPower,
      &tReflectedPower,
      &tAlarmCode,
      &tAlarmOnZeroPower);

   Prn::print(0, "tRet              %d",    tRet);
   Prn::print(0, "tForwardPower     %5.1f", tForwardPower);
   Prn::print(0, "tReflectedPower   %5.2f", tReflectedPower);
   Prn::print(0, "tAlarmCode        %c",    tAlarmCode);
   Prn::print(0, "tAlarmOnZeroPower %1d",   tAlarmOnZeroPower);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   char tString[200];

   while (true)
   {
      fgets(tString, 200, stdin);
      printf("CMD %d %s", (int)strlen(tString), tString);
      if (strcmp(tString, "e\n") == 0) break;
   }

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
}

