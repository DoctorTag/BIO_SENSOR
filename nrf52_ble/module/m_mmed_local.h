#ifndef M_MMED_LOCAL_H_
#define M_MMED_LOCAL_H_

typedef long	__S32_bit;
	typedef struct {
	    unsigned char b0:1;
	    unsigned char b1:1;
	    unsigned char b2:1;
	    unsigned char b3:1;
	    unsigned char b4:1;
	    unsigned char b5:1;
	    unsigned char b6:1;
	    unsigned char b7:1;
	    unsigned char b8:1;
	    unsigned char b9:1;
	    unsigned char b10:1;
	    unsigned char b11:1;
	    unsigned char b12:1;
	    unsigned char b13:1;
	    unsigned char b14:1;
	    unsigned char b15:1;
	    unsigned char b16:1;
	    unsigned char b17:1;
	    unsigned char b18:1;
	    unsigned char b19:1;
	    unsigned char b20:1;
	    unsigned char b21:1;
	    unsigned char b22:1;
	    unsigned char b23:1;
	    unsigned char b24:1;
	    unsigned char b25:1;
	    unsigned char b26:1;
	    unsigned char b27:1;
	    unsigned char b28:1;
	    unsigned char b29:1;
	    unsigned char b30:1;
	    unsigned char b31:1;

	} __32_bits;
	typedef union {
		struct
		{
			unsigned char byte0;
			unsigned char byte1;
			unsigned char byte2;
			unsigned char byte3;

		}byte;
	    __32_bits 		bits;
	    unsigned long 	u32;
	    long			s32;
	    
	} __32_type;


struct MMDTST_state{
	unsigned char state;
	unsigned char SamplingRate;
	unsigned char command;
};

typedef enum stMMDTST_RECORDER_STATE {
	
	IDLE_STATE =0,
	DATA_STREAMING_STATE,
	ACQUIRE_DATA_STATE,
	MMDTST_DOWNLOAD_STATE,
	MMDTST_RECORDING_STATE
}MMDTST_RECORDER_STATE;

#define START_DATA_HEADER			0x02
#define WRITE_REG_COMMAND			0x91
#define READ_REG_COMMAND			0x92
#define DATA_STREAMING_COMMAND		0x93
#define DATA_STREAMING_PACKET		0x93
#define ACQUIRE_DATA_COMMAND		0x94
#define ACQUIRE_DATA_PACKET 		0x94
#define PROC_DATA_DOWNLOAD_COMMAND	0x95
#define DATA_DOWNLOAD_COMMAND		0x96
#define FIRMWARE_UPGRADE_COMMAND	0x97
#define START_RECORDING_COMMAND		0x98
#define FIRMWARE_VERSION_REQ		0x99
#define STATUS_INFO_REQ 			0x9A
#define FILTER_SELECT_COMMAND		0x9B
#define ERASE_MEMORY_COMMAND		0x9C
#define RESTART_COMMAND				0x9D
#define END_DATA_HEADER				0x03


void m_mmed_local_init(void);
void m_local_uart_send_bytes(uint8_t *dbuf,uint16_t len,bool sceduled);
void m_mmed_local_hanlder(void * rdata,bool isanalog);

#define MMDTST_DATA_PACKET_LENGTH 6 // 3 Bytes (24 bits) * 1 Ch status + 2 Ch data = 3 * 3 = 9

#define MMDTST_ACQUIRE_PACKET_LENGTH 54	
#endif /*MMDTST_MAIN_H_*/
