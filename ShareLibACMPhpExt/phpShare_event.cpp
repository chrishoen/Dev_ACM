/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include <ctime>
#include <time.h>
#include <stdarg.h>

#include "smShare.h"
#include "phpShare.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Attempt to read a string from the event notification queue. If the queue
// is not empty then read the string and return it. If it is empty then return
// a null strring.

Php::Value share_tryEventNotifyQueueRead()
{
   char* tString = (char*)SM::gShare->mEventNotifyQueue.tryStartRead();
   return (Php::Value)tString;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Advance the event notification queue read index after using a string from
// the above try read call. Do no call this if the above read call returned
// a null string because there's nothing to advance.

void share_finishEventNotifyQueueRead()
{
   SM::gShare->mEventNotifyQueue.finishRead();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
