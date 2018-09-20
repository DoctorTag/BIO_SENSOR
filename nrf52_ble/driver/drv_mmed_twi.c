
#include <stdio.h>
#include "boards.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "nrf_drv_twi.h"
#include "nrf_delay.h"


#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#ifdef FEELKIT_WMMED_I2C

#include "drv_mmed_twi.h"

/* TWI instance ID. */
#define TWI_INSTANCE_ID     0

/* Common addresses definition for temperature sensor. */
#define MMED_ADDR          (0x88U >>1)

/* Indicates if operation on TWI has ended. */
static volatile bool mmed_twi_xfer_done  = false;

/* TWI instance. */
static const nrf_drv_twi_t mmed_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);

/* Buffer for samples read from temperature sensor. */
///static uint8_t m_sample;

static uint8_t mmed_twi_buf ;


/**
 * @brief TWI events handler.
 */
void mmed_twi_handler(nrf_drv_twi_evt_t const * p_event, void * p_context)
{
    switch (p_event->type)
    {
        case NRF_DRV_TWI_EVT_DONE:
            if (p_event->xfer_desc.type == NRF_DRV_TWI_XFER_RX)
            {
                // data_handler(m_sample);
            }
            mmed_twi_xfer_done  = true;
            break;
        default:
            break;
    }
}


void mmed_twi_init (void)
{
    ret_code_t err_code;

    const nrf_drv_twi_config_t twi_mmed_config =
    {
        .scl                = MMED_SCL_PIN,
        .sda                = MMED_SDA_PIN,
        .frequency          = NRF_TWI_FREQ_100K,
        .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
        .clear_bus_init     = false
    };

    err_code = nrf_drv_twi_init(&mmed_twi, &twi_mmed_config, mmed_twi_handler, NULL);
    APP_ERROR_CHECK(err_code);

    nrf_drv_twi_enable(&mmed_twi);
}

void mmed_twi_uninit (void)
{
    nrf_drv_twi_uninit(&mmed_twi);
}

ret_code_t mmed_twi_write(uint8_t *pdata,uint8_t len)
{
    mmed_twi_xfer_done  = false;
    ret_code_t err_code = nrf_drv_twi_tx(&mmed_twi, MMED_ADDR, pdata, len, false);
    APP_ERROR_CHECK(err_code);
    while (mmed_twi_xfer_done  == false)
    {
        __WFE();
    }

    return err_code;
}

ret_code_t mmed_twi_read(uint8_t reg,uint8_t *p_data,uint8_t len)
{
    mmed_twi_buf = reg;
    mmed_twi_xfer_done  = false;
    ret_code_t err_code = nrf_drv_twi_tx(&mmed_twi, MMED_ADDR, &mmed_twi_buf, 1, true);
    APP_ERROR_CHECK(err_code);
   while (mmed_twi_xfer_done  == false)
        {
         __WFE();
     }
   
     mmed_twi_xfer_done  = false;
    err_code = nrf_drv_twi_rx(&mmed_twi,MMED_ADDR, p_data, len);
    APP_ERROR_CHECK(err_code);
    while (mmed_twi_xfer_done  == false);
    {
        __WFE();
    }
    return err_code;
}



#endif
