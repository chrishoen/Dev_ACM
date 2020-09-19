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

#include "phpShare.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Regional variables.

// True if first time the functions is called.
bool mSystemTimeFirstFlag = true;

// Difference between localtime and UTC time.
int mTZOffsetSec = 0.0;
int mTZOffsetHour = 0;
int mTZOffsetMin = 0;

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get the system local time as a formatted string.
// Tue, 31 Mar 2020 14:09:27.012 - 4.0

Php::Value share_get_SystemTime()
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize mTimeZoneOffset.

   if (mSystemTimeFirstFlag)
   {
      mSystemTimeFirstFlag = false;

      time_t tCurrentTime;
      struct tm* tTimeInfo;
      time(&tCurrentTime);

      // Get utc time.
      tTimeInfo = gmtime(&tCurrentTime);
      time_t tUTCTime = mktime(tTimeInfo);

      // Get local time.
      tTimeInfo = localtime(&tCurrentTime);
      time_t tLocalTime = mktime(tTimeInfo);

      // Get offset in sec from UTC.
      mTZOffsetSec = (int)difftime(tLocalTime, tUTCTime);

      // Adjust for daylight savings time.
      if (tTimeInfo->tm_isdst)
      {
         mTZOffsetSec += 3600;
      }

      // Break down into hours and minutes.
      mTZOffsetHour = mTZOffsetSec / 3600;
      mTZOffsetMin = (mTZOffsetSec % 3600) / 60;

   }
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Tue, 31 Mar 2020 14:09:27.012 - 4.0

   // Get the current system time.
   struct timespec tSystemTime;
   timespec_get(&tSystemTime, TIME_UTC);

   // Format a string with it.
   char tBuffer1[40];
   char tBuffer2[80];
   strftime(tBuffer1, 40, "%a, %d %b %Y %T", localtime(&tSystemTime.tv_sec));
   sprintf(tBuffer2, "%s.%03ld %+03d:%02d", 
      tBuffer1, tSystemTime.tv_nsec / 1000000, 
      mTZOffsetHour, mTZOffsetMin);

   // Return the formatted string.
   return (Php::Value)tBuffer2;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
