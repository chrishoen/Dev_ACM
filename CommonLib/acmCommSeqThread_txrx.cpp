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

   // Send the string.
   mSerialStringThread->sendString(aString);
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

   // Send the string.
   mSerialStringThread->sendString(aString);
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