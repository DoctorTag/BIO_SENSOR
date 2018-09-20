/*******************************************************************************************************
 *
 *
 *
 *
 *
 * *****************************************************************************************************/
#include <stdint.h>
#include <string.h>

#include "boards.h"

//#include "sdk_config.h"
#include "app_uart.h"

#if defined (UART_PRESENT)
#include "nrf_uart.h"
#endif
#if defined (UARTE_PRESENT)
#include "nrf_uarte.h"
#endif
//#include "DSP_Filter.h"
#include "m_mmed_local.h"
// Function declarations
#include "drv_mmed.h"
#include "drv_mmed_adc.h"

#include "app_scheduler.h"
#include "nrf_pwr_mgmt.h"

unsigned short NumPackets, ReqSamples;
unsigned char NumFrames;
extern unsigned char MMDTSTRecorder_data_Buf[512], Recorder_head, Recorder_tail;
extern unsigned short Respiration_Rate ;
unsigned char *MMDTSTPacketAcqPrt;
unsigned char MMDTSTRecorder_data_Buf[512], Recorder_head = 0, Recorder_tail = 0;
unsigned int packetCounter = 0, AcqpacketCounter = 0;

extern unsigned int packetCounter , AcqpacketCounter;
extern unsigned short BlockNum;
extern unsigned char Store_data_rdy;

unsigned char KeyPressed = 0;
unsigned char keyCount = 0;

unsigned char Req_Dwnld_occured;

unsigned char LeadStatus = 0x0F;
// Global flags set by events

#define MAX_STR_LENGTH 64
//char wholeString[MAX_STR_LENGTH] = "";     // The entire input string from the last 'return'
unsigned int SlowToggle_Period = 20000 - 1;
unsigned int FastToggle_Period = 2000 - 1;
unsigned short Two_5millisec_Period = 60000;

unsigned int EcgPtr = 0;
unsigned char regval, Live_Streaming_flag = 0;


unsigned char MMDTSTTxPacket[64], MMDTSTTxCount, MMDTSTTxPacketRdy ;
unsigned char MMDTSTRxPacket[64], MMDTSTRxCount, dumy ;

struct MMDTST_state MMDTST_Recoder_state;
extern unsigned short Respiration_Rate;
unsigned short timeCtr = 0;

#define UART_TX_BUF_SIZE 256                         /**< UART TX buffer size. */
#define UART_RX_BUF_SIZE 256                         /**< UART RX buffer size. */
#define UDATA_LPLEN          32



unsigned char rstate;
unsigned short offset;

//void Stream_Adc_Data(unsigned char dtype,unsigned short rxdata);
//void Stream_Data(unsigned char dtype,unsigned short rxdata,bool isadc);
void Stream_Data(unsigned char dtype,unsigned short rxdata);
/* mmd */


#define SAMPLE_TYPE         SAMPLE_PPG


//#define ADC_FUN_TYPE            ADC_FUN_COMBO

unsigned char AdcFunType ;


void RecvInit();

void  RecvFrame( unsigned char src);

void Decode_Recieved_Command(void);
/*
static void uart_evt_sceduled(void * p_event_data, uint16_t event_size)
{
    RecvFrame(*( uint8_t*)p_event_data);
}
*/
static void rxcmd_evt_sceduled(void * p_event_data, uint16_t event_size)
{
    Decode_Recieved_Command();
}

static void local_utx_evt_sceduled(void * p_event_data, uint16_t event_size)
{
    uint16_t i;
   // uint8_t * sdata = (uint8_t *)p_event_data;
    for(i=0; i<MMDTSTTxCount; i++)
        while (app_uart_put(MMDTSTTxPacket[i]) != NRF_SUCCESS);

}

/**@brief   Function for handling app_uart events.
 *
 * @details This function will receive a single character from the app_uart module and append it to
 *          a string. The string will be be sent over BLE when the last character received was a
 *          'new line' '\n' (hex 0x0A) or if the string has reached the maximum data length.
 */
/**@snippet [Handling the data received over UART] */

void uart_event_handle(app_uart_evt_t * p_event)
{

    uint8_t udata;
    //  uint32_t       err_code;

    switch (p_event->evt_type)
    {
        case APP_UART_DATA_READY:
            UNUSED_VARIABLE(app_uart_get(&udata));
            RecvFrame( udata);

            break;

        case APP_UART_COMMUNICATION_ERROR:
            APP_ERROR_HANDLER(p_event->data.error_communication);
            break;

        case APP_UART_FIFO_ERROR:
            APP_ERROR_HANDLER(p_event->data.error_code);
            break;

        default:
            break;
    }
}


static void m_local_uart_init(void)
{
    uint32_t err_code;


    const app_uart_comm_params_t comm_params =
    {
        RX_PIN_NUMBER,
        TX_PIN_NUMBER,
        0xff, //RTS_PIN_NUMBER,
        0xff,// CTS_PIN_NUMBER,
        APP_UART_FLOW_CONTROL_DISABLED,
        false,
        NRF_UART_BAUDRATE_19200
    };

    APP_UART_FIFO_INIT(&comm_params,
                       UART_RX_BUF_SIZE,
                       UART_TX_BUF_SIZE,
                       uart_event_handle,
                       APP_IRQ_PRIORITY_LOWEST,
                       err_code);

    APP_ERROR_CHECK(err_code);

}
 uint32_t err_codeD;
void m_local_uart_send_bytes(uint8_t *dbuf,uint16_t len,bool sceduled)
{
#if NRF_MODULE_ENABLED(NRF_PWR_MGMT)
    //    nrf_pwr_mgmt_feed();
#endif

    if(sceduled)
    	{
          err_codeD = app_sched_event_put(0, 0, local_utx_evt_sceduled);
        APP_ERROR_CHECK(err_codeD  );
    	}
    else
    {
        uint16_t i;

        for(i=0; i<len; i++)
            while (app_uart_put(dbuf[i]) != NRF_SUCCESS);

    }

}

/*******************************************************************************************************
 *
 *
 *
 * *****************************************************************************************************/
void Decode_Recieved_Command(void)
{
    if (MMDTST_Recoder_state.state == IDLE_STATE)
    {
        switch(MMDTST_Recoder_state.command)
        {
                unsigned short strcpy_i;
            case WRITE_REG_COMMAND:     // Write Reg
            {

                if ( (MMDTSTRxPacket[2] < 12))
                {

                    //MMDTSTStop(ADC_FUN_TYPE);
                    //MMDTSTRxPacket[3] = 0x01;
                    //    mmdTestRegVal[MMDTSTRxPacket[2]] = MMDTSTRxPacket[3];
                }
                else
                {
                    MMDTSTRxPacket[2]  = 0;
                    MMDTSTRxPacket[3]  = 0;
                }

                for (strcpy_i = 0; strcpy_i < 7; strcpy_i++)
                {
                    MMDTSTTxPacket[strcpy_i] = MMDTSTRxPacket[strcpy_i]; // Prepare the outgoing string
                }

                MMDTSTTxCount = 7;
                MMDTSTTxPacketRdy = 1;

            }
            break;
            case READ_REG_COMMAND:  // Read Reg
            {

                if ( (MMDTSTRxPacket[2] < 12))
                {

                    //  MMDTSTStop(ADC_FUN_TYPE);

                    //MMDTSTRxPacket[3] = mmdTestRegVal[MMDTSTRxPacket[2]];

                    // MMDTST_Data_rdy = 0;
                    MMDTST_Recoder_state.state = IDLE_STATE;

                }
                else
                {
                    MMDTSTRxPacket[2]  = 0;
                    MMDTSTRxPacket[3]  = 0;
                }
                for (strcpy_i = 0; strcpy_i < 7; strcpy_i++)
                {
                    MMDTSTTxPacket[strcpy_i] = MMDTSTRxPacket[strcpy_i];                                    // Prepare the outgoing string
                }

                MMDTSTTxCount = 7;
                MMDTSTTxPacketRdy = 1;
            }
            break;
            case DATA_STREAMING_COMMAND:    // Data streaming
            {
                //       resetFilter();
               AdcFunType = MMDTSTRxPacket[3];
				drv_mmed_wrreg(RegNum_Peripheral, 0x0a);
                drv_mmed_wrcmd( MMDTSTRxPacket[2],MMDTSTRxPacket[3]);
                MMDTST_Recoder_state.state = DATA_STREAMING_STATE;  // Set to Live Streaming state
                Live_Streaming_flag = 1;                // Set Live Streaming Flag
                //MMDTST_Data_rdy = 0;




            }
            break;
            case ACQUIRE_DATA_COMMAND:  // Acquire Data

                break;

            case DATA_DOWNLOAD_COMMAND:     // RAW DATA DUMP
            {

            }
            break;

            case START_RECORDING_COMMAND:   // Processed Data Dump
            {
            }
            break;

            case FIRMWARE_UPGRADE_COMMAND:  // FIRMWARE UPGRADE

                break;
            case FIRMWARE_VERSION_REQ:  // firmware Version request
            {
                for (strcpy_i = 0; strcpy_i < 7; strcpy_i++)
                {
                    MMDTSTTxPacket[strcpy_i] = MMDTSTRxPacket[strcpy_i];
                    // Prepare the outgoing string
                }

                MMDTSTTxPacket[2] = 0x02;       // Firmware Major number
                MMDTSTTxPacket[3] = 0x0f;       // Firmware Minor number

                MMDTSTTxCount = 7;                              // number of bytes to send
                MMDTSTTxPacketRdy = 1;
            }
            break;

            case STATUS_INFO_REQ:   // Status Request
            {

            }
            break;
            case FILTER_SELECT_COMMAND:     // Filter Select request
            {
                if ( (MMDTSTRxPacket[2] < 4) && (MMDTSTRxPacket[2] != 1) )
                {
                    //  Filter_Option =  MMDTSTRxPacket[3];         // Filter option from user

                }
                else
                {
                    MMDTSTRxPacket[2]  = 0;
                    MMDTSTRxPacket[3]  = 0;
                }

                for (strcpy_i = 0; strcpy_i < 7; strcpy_i++)
                {
                    MMDTSTTxPacket[strcpy_i] = MMDTSTRxPacket[strcpy_i]; // Prepare the outgoing string
                }

                MMDTSTTxCount = 7;
                MMDTSTTxPacketRdy = 1;


            }
            break;
            case ERASE_MEMORY_COMMAND:  // MEMORY ERASE Command

            default:

                break;
        }
    }
    else
    {

        switch(MMDTST_Recoder_state.command)
        {

            case DATA_STREAMING_COMMAND:
            {
                if(AdcFunType == MMDTSTRxPacket[3])
                {
                              drv_mmed_wrcmd( MMDTSTRxPacket[2],MMDTSTRxPacket[3]);
 
               //     drv_mmed_stop( MMDTSTRxPacket[3]);
                    MMDTST_Recoder_state.state = IDLE_STATE;    // Switch to Idle state
                    //MMDTST_Data_rdy = 0;
                    Live_Streaming_flag = 0;            // Disable Live streaming flag
                }

            }
            break;
            default:

                break;
        }
    }
    MMDTST_Recoder_state.command = 0;
}

/*****************************************************************************************

*****************************************************************************************/
#define  RX_HEADER           0x00
#define  RX_CMD         0x01
//#define  RX_CODE        0x02
#define  RX_DATA           0x03
#define  RX_END            0x04

void RecvInit()
{
    rstate = RX_HEADER;
    offset = 0;

}
void  RecvFrame( unsigned char src)
{
    MMDTSTRxPacket[ offset] = src ;
    offset ++;


    switch(rstate)
    {
        case RX_HEADER:
            if(MMDTSTRxPacket[offset - 1] == START_DATA_HEADER)
            {
                rstate = RX_CMD;

            }
            else
            {
                RecvInit();
            }

            break;
        case RX_CMD:
            if((0x90 & MMDTSTRxPacket[offset - 1]) == 0x90)
            {
                rstate = RX_DATA;

            }
            else
            {
                RecvInit();
            }
            break;
        case RX_DATA:
            if(MMDTSTRxPacket[offset - 1] == END_DATA_HEADER)
            {
                rstate = RX_END;

            }
            if(offset >= MAX_STR_LENGTH )
            {
                RecvInit();
            }
            break;
        case RX_END:
            if(MMDTSTRxPacket[offset - 1] == 0x0a)
            {
                MMDTST_Recoder_state.command = MMDTSTRxPacket[1];
                //MMDTST_Recoder_state.command = readBytes;
                //   Decode_Recieved_Command();
                APP_ERROR_CHECK( app_sched_event_put(0, 0, rxcmd_evt_sceduled));


                RecvInit();
            }
            else
            {
                if(offset >= MAX_STR_LENGTH)
                {
                    RecvInit();
                }
                else if(MMDTSTRxPacket[offset - 1] != END_DATA_HEADER)
                    rstate = RX_DATA;

            }
            break;
    }



    //  return retvalue;
}


/*----------------------------------------------------------------------------+
| Main Routine                                                                |
+----------------------------------------------------------------------------*/
void m_mmed_local_init(void)
{
    Live_Streaming_flag = 0;
    MMDTST_Recoder_state.state = IDLE_STATE;
    MMDTST_Recoder_state.command = 0;


    m_local_uart_init();
    RecvInit();
    //MMDTSTFilter(0,1);
//   NormalizeData(0, 1);
    //  Filter_Noht_Init(250, 50, 0.005);
    //  Filter_Low_init(0.51);
    //  Filter_High_Init(250, 200);
//MMDTST_StreamCmd(1);
    //  Enable_Uart3_Receive_IT();


}


void m_mmed_local_hanlder(void * rdata,bool isanalog)
{
//    static uint8_t y0=0;

    switch(MMDTST_Recoder_state.state)
    {
        case IDLE_STATE:
        {
            if ( MMDTST_Recoder_state.command != 0)
            {
//                  Decode_Recieved_Command();
                MMDTST_Recoder_state.command = 0;
            }
        }
        break;
        case DATA_STREAMING_STATE:
        {


            if(isanalog)
            {
                uint8_t i;
                //uint16_t *tmpd = (uint16_t *)rdata;

                for(i=0; i<MMED_ADC_IN_BUFFER; i++)
                    //Stream_Adc_Data(SAMPLE_ECG,*(tmpd+i));
                    //   Stream_Adc_Data(SAMPLE_ECG,((uint16_t *)rdata)[i]);
                    Stream_Data(SAMPLE_ECG,((uint16_t *)rdata)[i]);
            }
            else
            {
                __32_type ad_val;
                uint8_t * tmpp = (uint8_t *)rdata;
                ad_val.byte.byte0 = tmpp[0];
                ad_val.byte.byte1 = tmpp[1];
                ad_val.byte.byte2 = tmpp[2];
                //    ad_val.byte.byte0 = 55;
                //  ad_val.byte.byte1 = 55;
                // ad_val.byte.byte2 = 55;

                ad_val.byte.byte3 = 0;
                // if((rxdata[3]   & 0xf0) == SAMPLE_TYPE)
                //  Stream_MMDTST_data_packets(ad_val.u32/256);
                Stream_Data(tmpp[3] & 0xf0,ad_val.u32/256);
            }




        }
        break;

        case ACQUIRE_DATA_STATE:


            break;
        case MMDTST_DOWNLOAD_STATE:

            // Send_Recorded_MMDTST_Samples_to_USB();

            break;

        case MMDTST_RECORDING_STATE:

            break;


        default:
            break;
    }




} //main()




#define PACK_SAMPLES 15
unsigned char StreamCount = 0;
static unsigned char sampleCNT = 0;
static short filterd;

void Stream_Data(unsigned char dtype,unsigned short rxdata)
{

    if ( sampleCNT > PACK_SAMPLES) sampleCNT = 0;

//    if (  MMDTST_Data_rdy == 1)
    {
        filterd = rxdata;
        //  filterd = afe4300_Filtered_MMDTST(rxdata);
        if ( sampleCNT == 0)
        {
            StreamCount = 0;
            MMDTSTTxPacket[StreamCount++] = START_DATA_HEADER;              // Packet start Header
            MMDTSTTxPacket[StreamCount++] = DATA_STREAMING_PACKET;          // Live MMDTST Streaming Header
            // LeadStatus = 0x00;

            //  LeadStatus = (unsigned char ) 0;
//           MMDTSTTxPacket[StreamCount++] = dtype ;
            // Set the Current Heart rate//
            MMDTSTTxPacket[StreamCount++] = 0;                  // Heart Rate
            // Set the current Leadoff status//
            MMDTSTTxPacket[StreamCount++] = 0;              // Respiration Rate
            MMDTSTTxPacket[StreamCount++] = 0 ;                 // Lead Status
        }
//       if ( sampleCNT > PACK_SAMPLES) sampleCNT = 0;
//       StreamCount = sampleCNT *3;                                   // Get Packet pointer
        //      StreamCount += 5;                                                   // Offset of 5 bytes header
        // for ( ucLoopCnt = 0 ; ucLoopCnt < 2; ucLoopCnt++)
        {
            MMDTSTTxPacket[StreamCount++] = dtype ;
            MMDTSTTxPacket[StreamCount++] = (filterd & 0x00FF);         // High Byte B15-B8
            MMDTSTTxPacket[StreamCount++] = ((filterd & 0xFF00) >> 8 );       // Low byte B7-B0

            //   MMDTSTTxPacket[StreamCount++] = (MMDTSTRawData[ucLoopCnt] & 0x00FF);           // High Byte B15-B8
            //   MMDTSTTxPacket[StreamCount++] = (MMDTSTRawData[ucLoopCnt] & 0xFF00) >> 8 ;     // Low byte B7-B0

        }
        sampleCNT++;
        if ( sampleCNT == PACK_SAMPLES)
        {
            sampleCNT = 0;
            MMDTSTTxPacket[StreamCount++] = END_DATA_HEADER;    // Packet end header
            MMDTSTTxPacket[StreamCount++] = '\n';
            //MMDTSTTxPacketRdy = 1;                      // Set packet ready flag after every 14th sample.
            MMDTSTTxCount = StreamCount;                    // Define number of bytes to send as 54.
            //   m_local_uart_send_bytes(MMDTSTTxPacket,StreamCount);
            m_local_uart_send_bytes(MMDTSTTxPacket,MMDTSTTxCount,true);
        }
        //MMDTST_Data_rdy = 0;
    }
}



/*----------------------------------------------------------------------------+
| End of source file                                                          |
+----------------------------------------------------------------------------*/
/*------------------------ Nothing Below This Line --------------------------*/
