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

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1       /* callback function: PanelCB */
#define  PANEL_PLOT                       2       /* control type: textButton, callback function: PlotData */
#define  PANEL_PAUSE                      3       /* control type: textButton, callback function: PauseChart */
#define  PANEL_QUIT                       4       /* control type: command, callback function: Shutdown */
#define  PANEL_RESP_CHART                 5       /* control type: strip, callback function: (none) */
#define  PANEL_PPG1_CHART_3               6       /* control type: strip, callback function: (none) */
#define  PANEL_PPG1_CHART_2               7       /* control type: strip, callback function: (none) */
#define  PANEL_PPG1_CHART                 8       /* control type: strip, callback function: (none) */
#define  PANEL_ECG_CHART                  9       /* control type: strip, callback function: (none) */
#define  PANEL_Ind1                       10      /* control type: numeric, callback function: (none) */

#define  PANEL_FWUP                       2
#define  PANEL_FWUP_FWUP_QUIT             2       /* control type: command, callback function: FWUP_QuitCb */
#define  PANEL_FWUP_LOAD_FILE             3       /* control type: command, callback function: LoadBinFileCb */
#define  PANEL_FWUP_PROGRESSBAR           4       /* control type: scale, callback function: (none) */
#define  PANEL_FWUP_TEXTMSG_2             5       /* control type: textMsg, callback function: (none) */
#define  PANEL_FWUP_FW_UPGRADE            6       /* control type: command, callback function: FWUpgradeCb */
#define  PANEL_FWUP_BIN_PATH              7       /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

#define  MENUBAR                          1
#define  MENUBAR_MENU1                    2
#define  MENUBAR_MENU1_ITEM1              3       /* callback function: ConfigMenuCallback */
#define  MENUBAR_MENU1_ITEM2              4       /* callback function: ConfigMenuCallback */


     /* Callback Prototypes: */

void CVICALLBACK ConfigMenuCallback(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK FWUP_QuitCb(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK FWUpgradeCb(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK LoadBinFileCb(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PanelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PauseChart(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PlotData(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Shutdown(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
