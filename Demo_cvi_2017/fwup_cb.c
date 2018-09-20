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
/* Include files                                                             */
/*---------------------------------------------------------------------------*/
#include <utility.h>
#include <cvirte.h>
#include <userint.h>
#include <ansi_c.h>
#include <progressbar.h>
#include <toolbox.h>
#include "bio_demo.h"
#include "serial.h"
#include "mmd_comm.h"
#include "fwup_cb.h"

#define PAGESIZE MAX_TDATA_LENGTH
#define PAGECNT 92

extern int FWUpgrade_handle;
extern int comport;

unsigned char *binBuf;

FILE * pfile;

// unsigned char tPageCnt;

int CVICALLBACK LoadBinFileCb (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		{
			char path[MAX_PATHNAME_LEN];
			binBuf = NULL;
			pfile = NULL;
			if (FileSelectPopupEx ("", "*.bin", "", "Select File to load",
								   VAL_OK_BUTTON, 0, 0, path) != VAL_NO_FILE_SELECTED)
			{

				/* Open the file and write out the data */
				pfile = fopen (path,"rb");
				if(pfile != NULL)
				{
					binBuf = (unsigned char*)malloc(MAX_TDATA_LENGTH*PAGECNT);
					if(binBuf != NULL)
					{
						size_t rcnt;
						fseek(pfile,0,SEEK_SET);
						rcnt = fread((void*)binBuf,PAGESIZE,PAGECNT, pfile);
						if(rcnt == PAGECNT)
						{

							SetCtrlVal (panel, PANEL_FWUP_BIN_PATH, path);
							//InsertListItem (panel, PANEL_ATTACHMENTS, -1, path, path);
							SetCtrlAttribute(panel,PANEL_FWUP_FW_UPGRADE,ATTR_DIMMED,0);
						}
						else
						{
							SetCtrlAttribute(panel,PANEL_FWUP_FW_UPGRADE,ATTR_DIMMED,1);
							MessagePopup ("Error:","Read bin file error!!");
						}
					}
					else
						MessagePopup ("Read Error:","Malloc error!!");
				}
				else
					MessagePopup ("Error:","Open bin file error!!");
			}


			break;
		}
	}
	return 0;
}


int CVICALLBACK FWUP_QuitCb (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		{
			if(binBuf != NULL)
			{
				free(binBuf);
				binBuf = NULL;
			}

			if(pfile != NULL)
			{
				fclose(pfile);
				pfile = NULL;
			}
			DiscardPanel (FWUpgrade_handle);
			break;
		}
	}
	return 0;
}

static void FWUpgradeReturnInd(int panel,char *tip,char *msg )
{


	SetCtrlAttribute(panel,PANEL_FWUP_PROGRESSBAR,ATTR_DIMMED,1);
	SetCtrlAttribute(panel,PANEL_FWUP_FWUP_QUIT,ATTR_DIMMED,0);
	SetCtrlAttribute(panel,PANEL_FWUP_FW_UPGRADE,ATTR_DIMMED,0);
	SetCtrlAttribute(panel,PANEL_FWUP_LOAD_FILE,ATTR_DIMMED,0);
	ProgressBar_Revert (panel, PANEL_FWUP_PROGRESSBAR);

	if((tip != NULL)&&(msg != NULL))
		MessagePopup (tip,msg);

}

int CVICALLBACK FWUpgradeCb (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	unsigned char bio_status,result,loop_cnt = 0;
	unsigned char *rspFrame;
	switch (event)
	{
		case EVENT_COMMIT:
		{
			ProgressBar_ConvertFromSlide (panel,PANEL_FWUP_PROGRESSBAR);
			ProgressBar_SetAttribute (panel,PANEL_FWUP_PROGRESSBAR, ATTR_PROGRESSBAR_UPDATE_MODE, VAL_PROGRESSBAR_MANUAL_MODE);

			SetCtrlAttribute(panel,PANEL_FWUP_PROGRESSBAR,ATTR_DIMMED,0);
			SetCtrlAttribute(panel,PANEL_FWUP_FWUP_QUIT,ATTR_DIMMED,1);
			SetCtrlAttribute(panel,PANEL_FWUP_FW_UPGRADE,ATTR_DIMMED,1);
			SetCtrlAttribute(panel,PANEL_FWUP_LOAD_FILE,ATTR_DIMMED,1);

			SetCtrlAttribute(panel,PANEL_FWUP_PROGRESSBAR,ATTR_LABEL_TEXT,"Device status requesting...");
			DisplayPanel (panel);
info_loop:
			if(loop_cnt > 3)
			{
				FWUpgradeReturnInd(panel,"BioSensor :","Sensor module info error !!!");
				//	MessagePopup ("BioSensor :","Sensor module info error !!!");
				return 0;
			}
			rspFrame = sendSyncCMDWithRsp(comport,STATUS_INFO_REQ,0,0,1000,&result);
			if(result)
			{
				bio_status = rspFrame[3];
				if(bio_status >= BIO_LOSE)
				{
					FWUpgradeReturnInd(panel,"BioSensor :","Sensor module lost !!!");
					//	MessagePopup ("BioSensor :","Sensor module lost !!!");
					return 0;
				}

			}
			else
			{
				FWUpgradeReturnInd(panel,NULL,NULL);
				return 0;

			}

			if(bio_status == BIO_NORMAL)   //is AP?
			{
				sendSyncCMDWithRsp(comport,RESTART_COMMAND,FWUPGRADE_RST,FWUP_PWD,1000,&result);
				if(result)
				{
					MessagePopup ("Tips:","RESTART_COMMAND RSP OK");
					Delay (2);
					loop_cnt++;
					goto info_loop;
				}
				else
				{
					FWUpgradeReturnInd(panel,NULL,NULL);
					return 0;

				}

			}

			rspFrame = sendSyncCMDWithRsp(comport,FIRMWARE_UPGRADE_CMD,BL_CMD_PROGRAM,FWUP_PWD,5000,&result);
			if(result == 0)
			{
				FWUpgradeReturnInd(panel,NULL,NULL);
				return 0;

			}
			else
			{
				if(rspFrame[4] != RSP_OK)
				{
					FWUpgradeReturnInd(panel,"Error :","BL_CMD_UPGRADE_REQ error !!!");
					//MessagePopup ("Error :","BL_CMD_UPGRADE_REQ error !!!");
					return 0;
				}
			}

			SetCtrlAttribute(panel,PANEL_FWUP_PROGRESSBAR,ATTR_LABEL_TEXT,"Erasing...");
			DisplayPanel (panel);

			sendSyncCMDWithRsp(comport,FIRMWARE_UPGRADE_CMD,BL_CMD_ERASEAPP,FWUP_PWD,15000,&result);

			if(result == 0)
			{
				FWUpgradeReturnInd(panel,NULL,NULL);
				return 0;

			}
			else
			{
				if(rspFrame[4] != RSP_OK)
				{
					FWUpgradeReturnInd(panel,"Error :","BL_CMD_ERASEAPP error !!!");
					//	MessagePopup ("Error :","BL_CMD_ERASEAPP error !!!");
					return 0;
				}
			}

			SetCtrlAttribute(panel,PANEL_FWUP_PROGRESSBAR,ATTR_LABEL_TEXT,"Programming...");
			DisplayPanel (panel);



			if(result)
			{


				unsigned char *Wrbuf = (unsigned char*)malloc(MAX_TDATA_LENGTH+MAX_TMISC_LENGTH);

				if(Wrbuf == NULL)
				{
					FWUpgradeReturnInd(panel,"Upgrade Error:","Malloc error!!");
					//	MessagePopup ("Upgrade Error:","Malloc error!!");
					return 0;
				}

				for(unsigned char pcnt = 0; pcnt < PAGECNT; pcnt++)
				{
					sendSyncAPUpgradeWithRsp(comport,Wrbuf,pcnt*(MAX_TDATA_LENGTH / 2),binBuf+pcnt*MAX_TDATA_LENGTH,MAX_TDATA_LENGTH,8000,&result) ;

					if(result == 0)
					{
						free(Wrbuf);
						FWUpgradeReturnInd(panel,NULL,NULL);
						return 0;
					}
					else
					{
						if(rspFrame[4] != RSP_OK)
						{
							char message[64]= {0};
							sprintf (message,"FIRMWARE_UPGRADING_COMMAND error= 0x%x !!", rspFrame[4]);
							//MessagePopup ("Error:",message);
							FWUpgradeReturnInd(panel,"Error:",message);
							free(Wrbuf);
							return 0;
						}
						//	else
						//	MessagePopup ("TIPS :","FIRMWARE_UPGRADING_COMMAND OK !!!");
					}

					ProgressBar_SetPercentage (panel, PANEL_FWUP_PROGRESSBAR, (100*pcnt)/PAGECNT, NULL);
					//	DisplayPanel (panel);

				}

				free(Wrbuf);

				sendSyncCMDWithRsp(comport,FIRMWARE_UPGRADE_CMD,BL_CMD_APRDY,FWUP_PWD,5000,&result);

				if(result == 0)
				{
					FWUpgradeReturnInd(panel,NULL,NULL);
					return 0;

				}
				else
				{
					if(rspFrame[4] != RSP_OK)
					{
						FWUpgradeReturnInd(panel,"Error :","BL_CMD_APRDY error !!!");
						//	MessagePopup ("Error :","BL_CMD_APRDY error !!!");
						return 0;
					}
				}

				SetCtrlAttribute(panel,PANEL_FWUP_PROGRESSBAR,ATTR_LABEL_TEXT,"Program OK");
				FWUpgradeReturnInd(panel,"Firmware upgrade:","Program OK!!");
				//	MessagePopup ("Firmware upgrade:","Program OK!!");
			}
			else
			{
				FWUpgradeReturnInd(panel,NULL,NULL);
				return 0;

			}


			break;
		}
	}
	return 0;
}
