#include "stdafx.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <phpcpp.h>

#include "MainInit.h"
#include "phpShare.h"
#include "smShare.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

extern "C"
{
	PHPCPP_EXPORT void * get_module()
	{
		main_initialize();

		static Php::Extension ex( "ShareLibACMPhpExt", "0.1" );

		ex.add<share_get_SuperStateACM_Json>("share_get_SuperStateACM_Json");
		ex.add<share_get_SuperSettingsACM_Json>("share_get_SuperSettingsACM_Json");

		//******************************************************************************
		//******************************************************************************
		//******************************************************************************

		return ex;
	}
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

class MyModuleInitClass
{
public:
	MyModuleInitClass()
	{
	}
	~MyModuleInitClass()
	{
		main_finalize();
	}
};

//******************************************************************************
//******************************************************************************
//******************************************************************************

MyModuleInitClass gMyModuleInitClassInstance;

//******************************************************************************
//******************************************************************************
//******************************************************************************

