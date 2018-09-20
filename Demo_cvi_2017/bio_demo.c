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

/*---------------------------------------------------------------------------*/
/* Include files                                                             */
/*---------------------------------------------------------------------------*/
#include <utility.h>
#include <cvirte.h>
#include <userint.h>
#include <ansi_c.h>
#include "bio_demo.h"
#include "serial.h"
#include "mmd_comm.h"
#include "fwup_cb.h"

volatile    int     LVSteamingFlag             =   0;
volatile  unsigned char SteamCBdata[2];

int ReadAdcData[32];
volatile int comport;
char comStr[4];
char msg[100];
//static      CmtTSQHandle        tsqHdl;
//static      int                 status;
//static      CmtThreadFunctionID LVSteamThreadFunctionID;

int hpanel,FWUpgrade_handle;



int CVICALLBACK LVSteamThreadFunction(void *callbackData) ;
/*---------------------------------------------------------------------------*/
/* This is the application's entry-point.                                    */
/*---------------------------------------------------------------------------*/
int main (int argc, char *argv[])
{

	int ret;
	LVSteamingFlag = 0;
	comport = 0;
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;

	PromptPopup ("Config COM Port", "COMx",comStr, 3);
	comport = atoi(comStr);
	ret = Init_ComPort (comport);
	if( ret != 0)
	{
		comport = 0;
		sprintf (msg, "Config COM port error: %d, please reconfig!!!",ret);
		MessagePopup ("This is a Message Popup",msg);
	};

	if ((hpanel = LoadPanel (0, "bio_demo.uir", PANEL)) < 0)
		return -1;


	/* Display the panel and run the UI */
	DisplayPanel (hpanel);
	RunUserInterface ();

	/* Free resources and return */
	if(comport > 0)
		ShutDownCom (comport)  ;
	DiscardPanel (hpanel);
	CloseCVIRTE ();
	return 0;
}

/*---------------------------------------------------------------------------*/
/* This function is called whenever any item in the Configuration or Test    */
/* menus is selected.  Notice that we are passed the menubar handle and item */
/* ID of the selected item.                                                  */
/*---------------------------------------------------------------------------*/
void CVICALLBACK ConfigMenuCallback (int menubar, int menuItem,
									 void *callbackData, int panel)
{
	int ret;
	switch (menuItem)
	{

			/* Take action depending on which item was selected */
		case MENUBAR_MENU1_ITEM1 :
			/* Run through a series of popups... */
			PromptPopup ("Config COM Port", "COMx",  comStr, 3);
			comport = atoi(comStr);
			ret = Init_ComPort (comport);
			if( ret != 0)
			{
				comport = 0;
				sprintf (msg, "Config COM port error: %d, please reconfig!!!",ret);
				MessagePopup ("This is a Message Popup",msg);
			};
			break;
		case MENUBAR_MENU1_ITEM2 :

			FWUpgrade_handle = LoadPanel (hpanel, "bio_demo.uir", PANEL_FWUP);
			InstallPopup (FWUpgrade_handle);

			break;

	}
}


/*---------------------------------------------------------------------------*/
/* Respond to the user's choice by enabling a timer which will plot data     */
/* continuously to a Stripchart.                                             */
/*---------------------------------------------------------------------------*/
int CVICALLBACK PlotData (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	int val, traces, i;
	unsigned char result;
	unsigned char *rspFrame;
	if (event == EVENT_COMMIT)
	{
		GetCtrlVal(panel, control, &val);
		// SetCtrlAttribute (panel, PANEL_TIMER, ATTR_ENABLED, val);
		LVSteamingFlag = val;
		if(val ==1)
		{
			//	SteamCBdata[0] = (REG_FUN2_ECG_D | M_FUN_START|OBEY_MODE);
			//			SteamCBdata[1] = 0;

			SteamCBdata[0] = (M_FUN_START|OBEY_MODE);
			//	SteamCBdata[1] = REG_FUN1_PPG_R;
			//	SteamCBdata[1] = REG_FUN1_RESP;
			//  SteamCBdata[1] = FUN1_COMBO_STD;
			SteamCBdata[1] = REG_FUN1_ECG_A;

			rspFrame  =	sendSyncCMDWithRsp(comport,DATA_STREAMING_COMMAND,SteamCBdata[0],SteamCBdata[1],1000,&result)  ;
			if(result == 0)
				return 0;
			else
			{
				if(rspFrame[4] != RSP_OK)
				{
					MessagePopup ("Error :","DATA_STREAMING_COMMAND error !!!");
					return 0;
				}
			}


			PostDeferredCallToThread (LVSteamThreadFunction, NULL, CmtGetMainThreadID ());
		}
		else
		{

			//	SteamData(comport,OBEY_MODE,SteamCBdata[1])   ;
			sendCMD(comport,DATA_STREAMING_COMMAND,OBEY_MODE,SteamCBdata[1])   ;
		}


		GetCtrlAttribute(panel, PANEL_RESP_CHART, ATTR_NUM_TRACES, &traces);
		for (i=1; i<=traces; i++)
			SetTraceAttribute(panel, PANEL_RESP_CHART, i, ATTR_TRACE_LG_VISIBLE, 1);


		GetCtrlAttribute(panel, PANEL_ECG_CHART, ATTR_NUM_TRACES, &traces);
		for (i=1; i<=traces; i++)
			SetTraceAttribute(panel, PANEL_ECG_CHART, i, ATTR_TRACE_LG_VISIBLE, 1);


		GetCtrlAttribute(panel, PANEL_PPG1_CHART, ATTR_NUM_TRACES, &traces);
		for (i=1; i<=traces; i++)
			SetTraceAttribute(panel, PANEL_PPG1_CHART, i, ATTR_TRACE_LG_VISIBLE, 1);

		GetCtrlAttribute(panel, PANEL_PPG1_CHART_2, ATTR_NUM_TRACES, &traces);
		for (i=1; i<=traces; i++)
			SetTraceAttribute(panel, PANEL_PPG1_CHART_2, i, ATTR_TRACE_LG_VISIBLE, 1);


		GetCtrlAttribute(panel, PANEL_PPG1_CHART_3, ATTR_NUM_TRACES, &traces);
		for (i=1; i<=traces; i++)
			SetTraceAttribute(panel, PANEL_PPG1_CHART_3, i, ATTR_TRACE_LG_VISIBLE, 1);

	}
	return 0;
}

/*---------------------------------------------------------------------------*/
/* Quit the UI loop.                                                         */
/*---------------------------------------------------------------------------*/
int CVICALLBACK Shutdown (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	if (event == EVENT_COMMIT)
	{
		if(LVSteamingFlag == 1)
			//	SteamData(comport,OBEY_MODE,SteamCBdata[1])   ;
			sendCMD(comport,DATA_STREAMING_COMMAND,OBEY_MODE,SteamCBdata[1])   ;
		LVSteamingFlag=0;
		QuitUserInterface (0);
	}
	return 0;
}


/*---------------------------------------------------------------------------*/
/* Pause the stripchart traces                                               */
/*---------------------------------------------------------------------------*/
int CVICALLBACK PauseChart (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	int val;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel, control, &val);
			SetCtrlAttribute(panel, PANEL_PPG1_CHART , ATTR_STRIP_CHART_PAUSED, val);
			SetCtrlAttribute(panel, PANEL_PPG1_CHART_2 , ATTR_STRIP_CHART_PAUSED, val);
			SetCtrlAttribute(panel, PANEL_PPG1_CHART_3 , ATTR_STRIP_CHART_PAUSED, val);


			SetCtrlAttribute(panel, PANEL_RESP_CHART , ATTR_STRIP_CHART_PAUSED, val);

			SetCtrlAttribute(panel, PANEL_ECG_CHART , ATTR_STRIP_CHART_PAUSED, val);

			break;
	}
	return 0;
}



int CVICALLBACK PanelCB (int panel, int event, void *callbackData,
						 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_CLOSE:
			if(LVSteamingFlag == 1)
				sendCMD(comport,DATA_STREAMING_COMMAND,OBEY_MODE,SteamCBdata[1])   ;
			//SteamData(comport,OBEY_MODE,SteamCBdata[1])   ;
			LVSteamingFlag=0;
			QuitUserInterface (0);
			break;
	}
	return 0;
}



int CVICALLBACK LVSteamThreadFunction(void *callbackData)
{
	double data_ld[1];

	unsigned char result,*ptrframe;


	short ADC_Data_ptr;
	double fout;





	RecvInit() ;
	while( LVSteamingFlag)
	{
		ptrframe = receiveSyncRspFrame(comport,500,&result) ;

		if(( ptrframe)&&(result == 0))
		{
			if(ptrframe[1] == DATA_STREAMING_PACKET)
			{
				ADC_Data_ptr = 0;                               // Set pointer
				ReadAdcData[ADC_Data_ptr++] = ptrframe[3];                 // Heart Rate
				ReadAdcData[ADC_Data_ptr++] = ptrframe[4];                 // Respiration Rate

				ReadAdcData[ADC_Data_ptr++] = ptrframe[5];                 // Lead STATUS
				// LeadStaus = Rdbuf[4];                                   // Lead STATUS
				for (short LC = 0; LC < PACK_SAMPLES; LC++)                       // Decode received packet of 15 samples.
				{
					ReadAdcData[LC+ADC_Data_ptr] =  ptrframe[LC*3 + 8];
					//  if (ReadAdcData[LC+ADC_Data_ptr] > 127)
					//      ReadAdcData[LC+ADC_Data_ptr]=ReadAdcData[LC+ADC_Data_ptr] -256;
					ReadAdcData[LC+ADC_Data_ptr] = ReadAdcData[LC+ADC_Data_ptr] << 8;
					ReadAdcData[LC+ADC_Data_ptr] |=  ptrframe[LC * 3+ 7];              // Channel 0 ( Resp or Lead I)

					// if(LC%2 == 1)
					{
						data_ld[0] =  ReadAdcData[LC+ADC_Data_ptr];

						/* Note how we plot three points at once, one for each trace */
						switch (ptrframe[LC*3 + 6])
						{
							case  SAMPLE_IMP:
								//case  SAMPLE_PPG_R:
							case  SAMPLE_ECG:
								//	case  SAMPLE_ECG_HF:
								//	case  SAMPLE_PPG_GDC:
								//	data_ld[0] =  ReadAdcData[LC+ADC_Data_ptr];
								PlotStripChart (hpanel, PANEL_ECG_CHART, data_ld, 1, 0, 0, VAL_DOUBLE);
								break;

							case  SAMPLE_PPG_G:
								//data_ppg[2]  =  ReadAdcData[LC+ADC_Data_ptr];
								PlotStripChart (hpanel, PANEL_PPG1_CHART, data_ld, 1, 0, 0, VAL_DOUBLE);
								break;
							case  SAMPLE_PPG_IR:
								PlotStripChart (hpanel, PANEL_PPG1_CHART_2, data_ld, 1, 0, 0, VAL_DOUBLE);
								break;
							case  SAMPLE_PPG_R:
								PlotStripChart (hpanel, PANEL_PPG1_CHART_3, data_ld, 1, 0, 0, VAL_DOUBLE);
								break;
								//		case  SAMPLE_PPG_IR:
							case  SAMPLE_RESP:
								//	data_ld[0] =  ReadAdcData[LC+ADC_Data_ptr];
								PlotStripChart (hpanel, PANEL_RESP_CHART, data_ld, 1, 0, 0, VAL_DOUBLE);
								break;

						}



					}

				}
			}
		}



		ProcessSystemEvents();
	}


	return 0;
}//DWORD WINAPI ThreadFunction(LPVOID iValue)
