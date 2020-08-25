/*==============================================================================
Detestion:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "acmCommSeqThread.h"

namespace ACM
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Send a null terminated string via the serial port. A newline terminator
// is appended to the string before transmission. This executes in the
// context of the The calling thread.

void CommSeqThread::sendString(const char* aString)
{
   // Guard.
   if (!mConnectionFlag)
   {
      Prn::print(Prn::View11, ">>>> NOT CONNECTED");
      return;
   }

   // Metrics.
   mTxCount++;

   // Print the string.
   Prn::print(Prn::View11, ">>>> %s", aString);

   // Send the string, no crlf
   mSerialStringThread->sendString(aString, false);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Send a null terminated string via the serial port. A newline terminator
// is appended to the string before transmission. This executes in the
// context of the The calling thread. The string is deleted after
// transmission.

void CommSeqThread::sendString(std::string* aString)
{
   // Guard.
   if (!mConnectionFlag)
   {
      Prn::print(Prn::View11, ">>>> NOT CONNECTED");
      delete aString;
      return;
   }

   // Metrics.
   mTxCount++;

   // Print the string.
   Prn::print(Prn::View11, ">>>> %s", aString->c_str());

   // Send the string, no crlf
   mSerialStringThread->sendString(aString, false);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Receive string qcall function. This is invoked by the child thread 
// when a string is received and it processes the received string
// in the context of the short thread.

void CommSeqThread::executeRxString(std::string* aString)
{
   // Metrics.
   mRxCount++;

   Prn::print(Prn::View11, "<<<< %s", aString->c_str());

   if (mShowCode == 1)
   {
      char tBuffer1[400];
      tBuffer1[0] = 0;
      for (int i = 0; i < aString->length(); i++)
      {
         char tBuffer2[10];
         sprintf(tBuffer2, "%02x ", (int)aString->c_str()[i]);
         strcat(tBuffer1, tBuffer2);
      }
      Prn::print(Prn::View11, "<<<< %s", tBuffer1);
   }

   // Write the string to the rx string queue and signal the notification
   // that an acknowledgement was received.
   if (mRxStringQueue.tryWrite(aString))
   {
      mNotify.notify(cCmdAckNotifyCode);
   }
   else
   {
      Prn::print(Prn::View11, "RxStringQueue FULL");
      delete aString;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace