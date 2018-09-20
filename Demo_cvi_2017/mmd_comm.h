
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



#ifndef MMD_COMM_H_
#define MMD_COMM_H_

#ifdef __cplusplus
extern "C" {
#endif

#define PACK_SAMPLES 15


#define SAMPLE_PPG_GDC	 0x00
#define SAMPLE_PPG_RDC   0x10
#define SAMPLE_PPG_IRDC	 0x20
#define SAMPLE_IMP		 0x30
#define SAMPLE_GSR		 0x40

#define SAMPLE_PPG_G	 0x70
#define SAMPLE_PPG_R	 0x80
#define SAMPLE_PPG_IR    0x90
#define SAMPLE_RESP		 0xa0

#define SAMPLE_ECG		 0xb0
#define SAMPLE_WH		 0xc0

#define SAMPLE_GSENSOR	 0xd0



#define REG_FUN1_ECG_A             0x01
#define REG_FUN1_PPG_R             0x02
#define REG_FUN1_PPG_G             0x04
#define REG_FUN1_PPG_IR            0x08
//#define REG_FUN1_PPG_DARK          0x10
#define REG_FUN1_IMP               0x20
#define REG_FUN1_RESP              0x40
#define REG_FUN1_GSR               0x80

#define REG_FUN2_ECG_D             0x01
#define REG_FUN2_WH                0x02

#define FUN1_COMBO_STD                (REG_FUN1_PPG_R|REG_FUN1_PPG_IR|REG_FUN1_RESP|REG_FUN1_GSR|REG_FUN1_PPG_G)

#define FUN1_COMBO_HR_RESP        (REG_FUN1_PPG_G|REG_FUN1_RESP)


#define M_FUN_START        0x10

#define HALT_MODE 	    0xe0
#define OBEY_MODE       0xc0
#define WATCH_MODE      0xa0
#define CAL_MODE        0x80
#define FWUP_MODE       0x60



#define START_DATA_HEADER			0x55
#define WRITE_REG_COMMAND			0x81
#define READ_REG_COMMAND			0x82
#define DATA_STREAMING_COMMAND		0x83
#define DATA_STREAMING_PACKET		0x83
#define ACQUIRE_DATA_COMMAND		0x84
#define ACQUIRE_DATA_PACKET 		0x84
#define DEVICE_ID_REQ              	0x85
#define DATA_DOWNLOAD_COMMAND		0x86
#define FIRMWARE_UPGRADE_CMD	    0x87
#define FIRMWARE_UPGRADING_COMMAND	0x88
#define FIRMWARE_VERSION_REQ		0x89
#define STATUS_INFO_REQ 			0x8A
#define FILTER_SELECT_COMMAND		0x8B
#define ERASE_MEMORY_COMMAND		0x8C
#define RESTART_COMMAND				0x8D
#define START_RECORDING_COMMAND		0x8E


#define END_DATA_HEADER				0x0A


#define AP_MASK				0x80

#define NORMAL_RST				    0x01
#define FWUPGRADE_RST				0x02

#define FWUP_PWD        0x58
#define RESET_PWD        0x68


#define BL_CMD_REBOOT    0X60
//#define BL_CMD_UPGRADE_REQ    0X61
#define BL_CMD_ERASEAPP    0X62
#define BL_CMD_JMPAPP    0X63
#define BL_CMD_APRDY    0X64
#define BL_CMD_PROGRAM    0X6f

	
#define RSP_OK                 (0x01)  /*! Command processed OK    */
#define RSP_PARA_ERROR     (0x02)  /*! Invalid parameters      */
#define RSP_CMD_ERROR  (0x03)  /*! Invalid command         */

#define RSP_ERASE_ERROR  (0x04)
#define RSP_PROGRAM_ERROR  (0x05)
#define RSP_CRC_ERROR  (0x06)
#define RSP_VERIFY_ERROR  (0x07)
#define RSP_UNKNOW                 (0x08)


#define MAX_TDATA_LENGTH 128

#define MAX_TMISC_LENGTH 8
	void RecvInit(void) ;
	unsigned char *  RecvFrame( unsigned char src,unsigned char *crc_error);
//	void SteamData(int com_port,unsigned char isbegin,unsigned char dtype);
	void sendCMD(int com_port,unsigned char cmd,unsigned char dtype0,unsigned char dtype) ;
	unsigned char *receiveSyncRspFrame(int com_port,int timeout,unsigned char *crc_error);
	unsigned char *sendSyncCMDWithRsp(int com_port,unsigned char cmd,unsigned char dtype0,unsigned char dtype,int timeout,unsigned char *result);
	unsigned char *sendSyncAPUpgradeWithRsp(int com_port,unsigned char *target,unsigned short offset,unsigned char *pdata,unsigned char pdlen,int timeout,unsigned char *result)
 ;

#ifdef __cplusplus
}
#endif

#endif /*MMDTST_MAIN_H_*/
