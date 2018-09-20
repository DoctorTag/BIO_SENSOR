/*---------------------------------------------------------------------------

BSD 3-Clause License

Copyright (c) 2018, feelkit
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of the copyright holder nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


---------------------------------------------------------------------------*/

/********************************************************************************************/
/* Include files                                                                            */
/********************************************************************************************/
#include <utility.h>
#include <rs232.h>
#include <ansi_c.h>
//#include <cvirte.h>
//#include <userint.h>
#include "serial.h"
#include <formatio.h>

/********************************************************************************************/
/* Constants                                                                                    */
/********************************************************************************************/
//#define COM_PORT    35
//int com_port;
/********************************************************************************************/
/* Globals                                                                                  */
/********************************************************************************************/


/********************************************************************************************/
/* Prototypes                                                                               */
/********************************************************************************************/
void CVICALLBACK Event_Char_Detect_Func (int portNo,int eventMask,void *callbackData);

/********************************************************************************************/
/* Application entry point.                                                                 */
/********************************************************************************************/
int Init_ComPort (int com_port)
{
	int RS232Error  ;
	DisableBreakOnLibraryErrors ();
	/*  Open and Configure Com port */
	RS232Error = OpenComConfig (com_port, "", 19200, 0, 8, 1, 512, 512);
	EnableBreakOnLibraryErrors ();

	if (RS232Error == 0)
	{ 
		/*  Turn off Hardware handshaking (loopback test will not function with it on) */
		SetCTSMode (com_port, LWRS_HWHANDSHAKE_OFF);

		/*  Make sure Serial buffers are empty */
		FlushInQ (com_port);
		FlushOutQ (com_port);
	}
 
	/*  Install a callback such that if the event character appears at the
		receive buffer, our function will be notified.  */
//  InstallComCallback (COM_PORT, LWRS_RXFLAG, 0, (int)gEventChar[0] , Event_Char_Detect_Func, 0);

	return RS232Error;
}

/********************************************************************************************/
/* SendData ():  Respond to the Send button to send characters out of the serial port.      */
/********************************************************************************************/
int SendData (int com_port,unsigned char *data,int dlen)
{
	if(com_port < 1)
		 return 0;
	FlushInQ (com_port);
	ComWrt (com_port, data, dlen);
	return dlen;
}

/********************************************************************************************/
/* Event_Char_Detect_Func ():  Fuction called when the event character is detected.         */
/********************************************************************************************/
void CVICALLBACK Event_Char_Detect_Func (int portNo,int eventMask,void *callbackData)
{
	return;
}



/********************************************************************************************/
/* ReceiveData ():  Read the data on the serial COM port.                                   */
/********************************************************************************************/
int  ReceiveData (int com_port,unsigned char *buf,int buflen)
{
	int     strLen;

	 if(com_port < 1)
		 return 0;
	/*  Read the characters from the port */
	strLen = GetInQLen (com_port);
	if(strLen > buflen)
		strLen = buflen;
	ComRd (com_port, buf, strLen);

	return strLen;
}

int ShutDownCom (int com_port)
{  
	return  CloseCom(com_port);
}
