#include "stdafx.h"

#include "cmnProgramParms.h"
#include "smShare.h"
#include "acmCommSeqThread.h"

#include "CmdLineExec.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

CmdLineExec::CmdLineExec()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
void CmdLineExec::reset()
{
}
//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("TP"))        ACM::gCommSeqThread->mTPFlag = aCmd->argBool(1);

   if (aCmd->isCmd("PROC"))      executeProcess(aCmd);
   if (aCmd->isCmd("A"))         executeAbort(aCmd);
   if (aCmd->isCmd("REQ"))       executeRequest(aCmd);
   if (aCmd->isCmd("OVER"))      executeOverride(aCmd);

   if (aCmd->isCmd("GO1"))       executeGo1(aCmd);
   if (aCmd->isCmd("GO2"))       executeGo2(aCmd);
   if (aCmd->isCmd("GO3"))       executeGo3(aCmd);
   if (aCmd->isCmd("GO4"))       executeGo4(aCmd);


   if (aCmd->isCmd("Help"))      executeHelp(aCmd);
   if (aCmd->isCmd("Parms"))     executeParms(aCmd);
   if (aCmd->isCmd("Show"))      executeShow(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeProcess(Ris::CmdLineCmd* aCmd)
{
   ACM::gCommSeqThread->mProcessQCall();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeAbort(Ris::CmdLineCmd* aCmd)
{
   ACM::gCommSeqThread->mAbortQCall();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeRequest(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->numArg() == 0)
   {
      Prn::print(0, " 0  ReadAllSettings");
      Prn::print(0, " 1  LowPowerThresh_pct      float");
      Prn::print(0, " 2  LowPowerAlarmEnable     bool");
      Prn::print(0, " 3  HighPowerThresh_pct     float");
      Prn::print(0, " 4  HighPowerAlarmEnable    bool");
      Prn::print(0, " 5  VSWRTrigger             int");
      Prn::print(0, " 6  VSWRAlarmEnable         bool");
      Prn::print(0, " 7  Gain                    int int");
      Prn::print(0, " 8  LatchAlarmEnable        bool");
      Prn::print(0, " 9  PowerUpAlarmEnable      bool");
      Prn::print(0, "10  RelayOnAlarmEnable      bool");
      Prn::print(0, "11  VSWROnZeroEnable        bool");
      Prn::print(0, "12  PTTDelay_sec            float");
      Prn::print(0, "13  PTTAlarmEnable          bool");
      return;
   }

   int tV = aCmd->argInt(1);
   ACM::SuperSettingsACM* tS = &SM::gShare->mSuperSettingsACM;
   switch (tV)
   {
   case  0:  tS->requestReadAllSettings(); break;
   case  1:  tS->requestLowPowerThresh_pct(aCmd->argDouble(2)); break;
   case  2:  tS->requestLowPowerAlarmEnable(aCmd->argBool(2)); break;
   case  3:  tS->requestHighPowerThresh_pct(aCmd->argDouble(2)); break;
   case  4:  tS->requestHighPowerAlarmEnable(aCmd->argBool(2)); break;
   case  5:  tS->requestVSWRTrigger(aCmd->argInt(2)); break;
   case  6:  tS->requestVSWRAlarmEnable(aCmd->argBool(2)); break;
   case  7:  tS->requestGain(aCmd->argInt(2), aCmd->argDouble(3)); break;
   case  8:  tS->requestLatchAlarmEnable(aCmd->argBool(2)); break;
   case  9:  tS->requestPowerUpAlarmEnable(aCmd->argBool(2)); break;
   case 10:  tS->requestRelayOnAlarmEnable(aCmd->argBool(2)); break;
   case 11:  tS->requestVSWROnZeroEnable(aCmd->argBool(2)); break;
   case 12:  tS->requestPTTDelay_sec(aCmd->argDouble(2)); break;
   case 13:  tS->requestPTTAlarmEnable(aCmd->argBool(2)); break;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeOverride(Ris::CmdLineCmd* aCmd)
{
   SM::gShare->mSuperStateACM.mOverrideForwardPower_w = aCmd->argDouble(1);
   SM::gShare->mSuperStateACM.mOverrideReflectedPower_w = aCmd->argDouble(2);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   ACM::gCommSeqThread->sendString(aCmd->argString(1));
   return;

   char tString[100];
   sprintf(tString, "B");
   ACM::gCommSeqThread->sendString(tString);

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   Prn::print(Prn::View11, "GO1**************");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
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

void CmdLineExec::executeParms(Ris::CmdLineCmd* aCmd)
{
   Cmn::gProgramParms.show();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeHelp(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "Help ***********************************");
   Prn::print(0, "");
   Prn::print(0, "proc                 -- start main processing loop");
   Prn::print(0, "a                    -- abort main processing loop");
   Prn::print(0, "tp bool1             -- enable/disable periodic superstate acquire");

   Prn::print(0, "");
   Prn::print(0, "over float1 float2   -- override input super state forward and reflected power watts");
   Prn::print(0, "show x               -- show super state");
   Prn::print(0, "show s               -- show super settings");
   Prn::print(0, "");
   Prn::print(0, "req                  -- show super settings request options");
   Prn::print(0, "req option int1      -- request setting a super setting value");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeShow(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isArgString(1, "X"))
   {
      SM::gShare->mSuperStateACM.show();
   }
   else if (aCmd->isArgString(1, "S"))
   {
      SM::gShare->mSuperSettingsACM.show();
   }
}

