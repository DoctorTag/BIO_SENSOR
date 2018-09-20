
#include "nrf_drv_spi.h"
#include "app_util_platform.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "boards.h"
#include "app_error.h"
#include <string.h>
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#ifdef FEELKIT_WMMED_SPI
#include "nrf_drv_gpiote.h"

#include "nrf_drv_spi.h"

#define MMED_SPI_DELY_US        200

#define MMED_SPI_DEFAULT_CONFIG                           \
{                                                            \
    .sck_pin      = MMED_SPI_SCK_PIN,                \
    .mosi_pin     = MMED_SPI_MOSI_PIN,                \
    .miso_pin     = MMED_SPI_MISO_PIN,                \
    .ss_pin       = NRF_DRV_SPI_PIN_NOT_USED,                \
    .irq_priority = MMED_SPI_IRQ_PRIORITY,         \
    .orc          = 0xff,                                    \
    .frequency    = NRF_DRV_SPI_FREQ_125K,                     \
    .mode         = NRF_DRV_SPI_MODE_1,                      \
    .bit_order    = NRF_DRV_SPI_BIT_ORDER_MSB_FIRST,         \
}

#define MMED_SPI_INSTANCE  0 /**< SPI instance index. */
static const nrf_drv_spi_t mmed_spi = NRF_DRV_SPI_INSTANCE(MMED_SPI_INSTANCE);  /**< SPI instance. */
static volatile bool mmed_xfer_done;  /**< Flag used to indicate that SPI instance completed the transfer. */

//static uint8_t mmed_spi_rxbuf[2] ;
//static uint8_t mmed_spi_txbuf[2];
static uint8_t mmed_spi_buf;



/**
 * @brief SPI user event handler.
 * @param event
 */
static void mmed_spi_event_handler(nrf_drv_spi_evt_t const * p_event,void *p_context)
{
    mmed_xfer_done = true;
}

void mmed_spi_init (void)
{
    ret_code_t  err_code;
    if (!nrf_drv_gpiote_is_init())
    {
        err_code = nrf_drv_gpiote_init();
        APP_ERROR_CHECK(err_code);
    }

    nrf_drv_gpiote_out_config_t out_config = GPIOTE_CONFIG_OUT_SIMPLE(true);

    err_code = nrf_drv_gpiote_out_init(MMED_SPI_SS_PIN, &out_config);
    APP_ERROR_CHECK(err_code);

    nrf_drv_spi_config_t spi_config = MMED_SPI_DEFAULT_CONFIG;
    APP_ERROR_CHECK(nrf_drv_spi_init(&mmed_spi, &spi_config, mmed_spi_event_handler, NULL));
}

void mmed_spi_uninit (void)
{
    nrf_drv_spi_uninit(&mmed_spi);
    nrf_drv_gpiote_out_uninit(MMED_SPI_SS_PIN);

}


uint8_t mmed_spi_read( uint8_t reg)
{

    mmed_spi_buf = (0x80|reg);
    mmed_xfer_done = false;
    nrf_drv_gpiote_out_clear(MMED_SPI_SS_PIN);
    APP_ERROR_CHECK(nrf_drv_spi_transfer(&mmed_spi, &mmed_spi_buf,1,NULL,0));

    while (!mmed_xfer_done)
    {
        __WFE();
    }
    nrf_delay_us(MMED_SPI_DELY_US);
    //mmed_spi_txbuf[0] =0x0;
    mmed_xfer_done = false;
    APP_ERROR_CHECK(nrf_drv_spi_transfer(&mmed_spi, NULL,0,&mmed_spi_buf,1));

    while (!mmed_xfer_done)
    {
        __WFE();
    }
    nrf_delay_us(MMED_SPI_DELY_US);
    nrf_drv_gpiote_out_set(MMED_SPI_SS_PIN);
    return mmed_spi_buf;

}


void mmed_spi_write( uint8_t reg,uint8_t data)
{

    mmed_spi_buf = reg;

    mmed_xfer_done = false;
    nrf_drv_gpiote_out_clear(MMED_SPI_SS_PIN);
    APP_ERROR_CHECK(nrf_drv_spi_transfer(&mmed_spi, &mmed_spi_buf,1, NULL,0));
    nrf_delay_us(MMED_SPI_DELY_US);
    while (!mmed_xfer_done)
    {
        __WFE();
    }

    mmed_spi_buf = data;
    mmed_xfer_done = false;
    APP_ERROR_CHECK(nrf_drv_spi_transfer(&mmed_spi, &mmed_spi_buf,1, NULL,0));
    nrf_delay_us(MMED_SPI_DELY_US);
    while (!mmed_xfer_done)
    {
        __WFE();
    }

    nrf_drv_gpiote_out_set(MMED_SPI_SS_PIN);


}

#endif
