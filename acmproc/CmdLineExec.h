#pragma once

#include "risCmdLineExec.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

class CmdLineExec : public Ris::BaseCmdLineExec
{
public:

  CmdLineExec();

  void reset();
  void execute(Ris::CmdLineCmd* aCmd);

  void executeProcess  (Ris::CmdLineCmd* aCmd);
  void executeAbort    (Ris::CmdLineCmd* aCmd);
  void executeRequest  (Ris::CmdLineCmd* aCmd);
  void executeOverride (Ris::CmdLineCmd* aCmd);

  void executeTx       (Ris::CmdLineCmd* aCmd);
  void executeGo1      (Ris::CmdLineCmd* aCmd);
  void executeGo2      (Ris::CmdLineCmd* aCmd);
  void executeGo3      (Ris::CmdLineCmd* aCmd);
  void executeGo4      (Ris::CmdLineCmd* aCmd);

  void executeHelp     (Ris::CmdLineCmd* aCmd);
  void executeParms    (Ris::CmdLineCmd* aCmd);
  void executeShow     (Ris::CmdLineCmd* aCmd);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************

