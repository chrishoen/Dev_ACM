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
   if (aCmd->isCmd("PROC"))      executeProcess(aCmd);
   if (aCmd->isCmd("A"))         executeAbort(aCmd);
   if (aCmd->isCmd("REQ"))       executeRequest(aCmd);

   if (aCmd->isCmd("GO1"))       executeGo1(aCmd);
   if (aCmd->isCmd("GO2"))       executeGo2(aCmd);
   if (aCmd->isCmd("GO3"))       executeGo3(aCmd);
   if (aCmd->isCmd("GO4"))       executeGo4(aCmd);


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
      Prn::print(0, "10  RelayOnPowerEnable(     bool");
      Prn::print(0, "11  RelayOnVSWREnable(      bool");
      Prn::print(0, "12  CheckVSWROnZeroEnable   bool");
      Prn::print(0, "13  PTTDelay_sec            float");
      Prn::print(0, "14  PTTAlarmEnable          bool");
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
   case 10:  tS->requestRelayOnPowerEnable(aCmd->argBool(2)); break;
   case 11:  tS->requestRelayOnVSWREnable(aCmd->argBool(2)); break;
   case 12:  tS->requestCheckVSWROnZeroEnable(aCmd->argBool(2)); break;
   case 13:  tS->requestPTTDelay_sec(aCmd->argDouble(2)); break;
   case 14:  tS->requestPTTAlarmEnable(aCmd->argBool(2)); break;
   }
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

