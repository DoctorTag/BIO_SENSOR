
#include "app_util_platform.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "boards.h"
#include "app_error.h"
#include <string.h>
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_drv_gpiote.h"
#include "nrf_pwr_mgmt.h"

#include "app_scheduler.h"
#include "drv_mmed.h"
#include "drv_mmed_adc.h"
#ifdef FEELKIT_WMMED_I2C
#include "drv_mmed_twi.h"

#endif

#ifdef FEELKIT_WMMED_SPI
#include "drv_mmed_spi.h"

#endif


//#define MMED_RXD_LEN      8
#ifdef FEELKIT_WMMED_SPI
static uint8_t mmed_rdreg[4]= {RegNum_Addl ,RegNum_Addm,RegNum_Addh, RegNum_Ad_Type_Cnt };
#endif
static uint8_t mmed_rxdata[4]= {0x00 ,0x00,0x00, 0x00 };


mmed_drdy_evt_handler_t drdy_evt_cb ;      ///< Callback. Invoked when a pin interrupt is caught by GPIOTE.




uint8_t drv_mmed_rdreg( uint8_t reg)
{
#ifdef FEELKIT_WMMED_I2C

    mmed_twi_read(reg,mmed_rxdata,1);
    return mmed_rxdata[0];
#endif

#ifdef FEELKIT_WMMED_SPI


    return mmed_spi_read(reg);


#endif



}


void drv_mmed_wrreg( uint8_t reg,uint8_t data)
{

#ifdef FEELKIT_WMMED_I2C

    mmed_rxdata[0] = reg;
    mmed_rxdata[1] = data;

    mmed_twi_write(mmed_rxdata,2);


#endif

#ifdef FEELKIT_WMMED_SPI

    mmed_spi_write(reg,data);

#endif



}

void drv_mmed_adc_read(void)
{
#ifdef FEELKIT_WMMED_I2C
   mmed_twi_read(RegNum_Addl ,mmed_rxdata,4);
/*
  uint8_t   i;

    for(i=0; i<4; i++)
    {
       // mmed_rxdata[i] = mmed_spi_read( mmed_rdreg[i]);
mmed_twi_read(mmed_rdreg[i] ,mmed_rxdata+i,1);
    }
*/
#endif

#ifdef FEELKIT_WMMED_SPI

    uint8_t   i;

    for(i=0; i<4; i++)
    {
        mmed_rxdata[i] = mmed_spi_read( mmed_rdreg[i]);

    }



#endif

}
/*
static void mmed_drdy_evt_sceduled(void * p_event_data, uint16_t event_size)
{

}
*/
void mmed_drdy_evt_sceduled(void * p_event_data, uint16_t event_size)
{
    drv_mmed_adc_read();
    drdy_evt_cb(mmed_rxdata,false);
}

static void drdy_evt_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
    uint32_t err_code;

    // if ((pin == MMED_DRDY_INT ) && (nrf_gpio_pin_read(MMED_DRDY_INT) == 1))
    if (pin == MMED_DRDY_INT )
    {
        //  bsp_board_led_invert(0);
//nrf_pwr_mgmt_feed();
        //   drv_mmed_rdbytes(mmed_rdreg,mmed_rxdata[mmed_rxd_ccnt],4);

        err_code = app_sched_event_put(0, 0, mmed_drdy_evt_sceduled);
        APP_ERROR_CHECK(err_code);


    }
}


static uint32_t drdy_gpiote_init(uint32_t pin)
{
    uint32_t err_code;


    if (!nrf_drv_gpiote_is_init())
    {
        err_code = nrf_drv_gpiote_init();
        APP_ERROR_CHECK(err_code);
    }

    nrf_drv_gpiote_in_config_t gpiote_in_config=  GPIOTE_CONFIG_IN_SENSE_LOTOHI(true);
    gpiote_in_config.pull = NRF_GPIO_PIN_PULLUP;
    //gpiote_in_config.is_watcher = true;
    err_code = nrf_drv_gpiote_in_init(pin, &gpiote_in_config, drdy_evt_handler);
    APP_ERROR_CHECK(err_code);
    //nrf_drv_gpiote_in_event_enable(MMED_DRDY_INT,true);


#if defined MMED_TEST_IND

    err_code = nrf_drv_gpiote_out_init(MMED_TEST_IND, &out_config);
    APP_ERROR_CHECK(err_code);


#endif
    return NRF_SUCCESS;
}

#if defined MMED_TEST_IND

void drv_mmed_test_ind(bool isset)
{
    if(isset)
        nrf_drv_gpiote_out_set(MMED_TEST_IND);

    else
        nrf_drv_gpiote_out_clear(MMED_TEST_IND);

}

#endif

void drv_mmed_init(mmed_drdy_evt_handler_t handler  )
{
#ifdef FEELKIT_WMMED_I2C

    mmed_twi_init ();

#endif

#ifdef FEELKIT_WMMED_SPI

    mmed_spi_init ();
#endif

    drdy_gpiote_init(MMED_DRDY_INT );
    drdy_evt_cb = handler;
}


void drv_mmed_uninit(void)
{

    //
    nrf_drv_gpiote_in_uninit(MMED_DRDY_INT );
#ifdef FEELKIT_WMMED_I2C

    mmed_twi_uninit ();

#endif

#ifdef FEELKIT_WMMED_SPI

    mmed_spi_uninit ();
#endif
}
/*
void drv_mmed_start(uint8_t type)
{
   if(type != ADC_FUN_ECG_HF )
    {
        nrf_drv_gpiote_in_event_enable(MMED_DRDY_INT, true);
    }
    drv_mmed_wrreg(RegNum_Sam_Action,  type|MMED_ADC_START);

    if((type&ADC_FUN_ECG_HF) == ADC_FUN_ECG_HF )
      saadc_sampling_event_enable(true);

}


void drv_mmed_stop(uint8_t type)
{
    drv_mmed_wrreg(RegNum_Sam_Action,  type);

    if((type&ADC_FUN_ECG_HF) == ADC_FUN_ECG_HF )
        saadc_sampling_event_enable(false);
    if(type != ADC_FUN_ECG_HF )
    {
        nrf_drv_gpiote_in_event_disable(MMED_DRDY_INT);
    }

}
*/

void drv_mmed_wrcmd(uint8_t reg_mfun2,uint8_t reg_fun1)
{
    drv_mmed_wrreg(RegNum_Fun1,  reg_fun1);
    if(reg_mfun2 &M_FUN_START)
    {
        if(reg_fun1 != REG_FUN1_ECG_A )
        {
            nrf_drv_gpiote_in_event_enable(MMED_DRDY_INT, true);
        }




        if((reg_fun1&REG_FUN1_ECG_A ) == REG_FUN1_ECG_A  )
            saadc_sampling_event_enable(true);

        drv_mmed_wrreg(RegNum_RMode_Fun2,  reg_mfun2);

    }
    else
    {
        drv_mmed_wrreg(RegNum_RMode_Fun2,  reg_mfun2);

        if((reg_fun1&REG_FUN1_ECG_A) == REG_FUN1_ECG_A )
            saadc_sampling_event_enable(false);
        if(reg_fun1 != REG_FUN1_ECG_A )
        {
            nrf_drv_gpiote_in_event_disable(MMED_DRDY_INT);
        }
    }
}

