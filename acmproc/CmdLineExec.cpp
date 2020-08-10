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
   if (aCmd->isCmd("ACQ"))       executeAcquire(aCmd);
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

void CmdLineExec::executeAcquire(Ris::CmdLineCmd* aCmd)
{
   ACM::gCommSeqThread->mAcquireQCall();
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
   int tV = aCmd->argInt(1);
   if (tV == 0)
   {
      Prn::print(0, " 1  LowPowerThresh_pct      float");
      Prn::print(0, " 2  LowPowerAlarmEnable     bool");
      Prn::print(0, " 3  HighPowerThresh_pct     float");
      Prn::print(0, " 4  HighPowerAlarmEnable    bool");
      Prn::print(0, " 5  Gain                    int int");
      Prn::print(0, " 6  LatchAlarmEnable        bool");
      Prn::print(0, " 7  PowerUpAlarmEnable      bool");
      Prn::print(0, " 8  RelayOnPowerEnable(     bool");
      Prn::print(0, " 9  RelayOnVSWREnable(      bool");
      Prn::print(0, "10  CheckVSWROnZeroEnable   bool");
      Prn::print(0, "11  PTTDelay_sec            float");
      Prn::print(0, "12  PTTAlarmEnable          bool");
      return;
   }

   ACM::SuperSettingsACM* tS = &SM::gShare->mSuperSettingsACM;
   switch (tV)
   {
   case  1:  tS->requestLowPowerThresh_pct(aCmd->argDouble(2)); break;
   case  2:  tS->requestLowPowerAlarmEnable(aCmd->argBool(2)); break;
   case  3:  tS->requestHighPowerThresh_pct(aCmd->argDouble(2)); break;
   case  4:  tS->requestHighPowerAlarmEnable(aCmd->argBool(2)); break;
   case  5:  tS->requestGain(aCmd->argInt(2), aCmd->argDouble(3)); break;
   case  6:  tS->requestLatchAlarmEnable(aCmd->argBool(2)); break;
   case  7:  tS->requestPowerUpAlarmEnable(aCmd->argBool(2)); break;
   case  8:  tS->requestRelayOnPowerEnable(aCmd->argBool(2)); break;
   case  9:  tS->requestRelayOnVSWREnable(aCmd->argBool(2)); break;
   case 10:  tS->requestCheckVSWROnZeroEnable(aCmd->argBool(2)); break;
   case 11:  tS->requestPTTDelay_sec(aCmd->argDouble(2)); break;
   case 12:  tS->requestPTTAlarmEnable(aCmd->argBool(2)); break;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   Prn::print(Prn::View11, "GO1");
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

