/**
 * Copyright (c) 2014 - 2017, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/** @file
 * @defgroup nrf_adc_example main.c
 * @{
 * @ingroup nrf_adc_example
 * @brief ADC Example Application main file.
 *
 * This file contains the source code for a sample application using ADC.
 *
 * @image html example_board_setup_a.jpg "Use board setup A for this example."
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "nrf.h"
#include "nrf_drv_saadc.h"
#include "nrf_drv_ppi.h"
#include "nrf_drv_timer.h"
#include "boards.h"
#include "app_error.h"
#include "nrf_delay.h"
#include "app_util_platform.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_drv_power.h"

#include "app_scheduler.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "drv_mmed.h"
#include "drv_mmed_adc.h"

mmed_drdy_evt_handler_t adc_drdy_evt_cb ;      ///< Callback. Invoked when a pin interrupt is caught by GPIOTE.


volatile uint8_t state = 1;

static const nrf_drv_timer_t m_timer = NRF_DRV_TIMER_INSTANCE(1);
static nrf_saadc_value_t     m_buffer_pool[2][MMED_ADC_IN_BUFFER];
static nrf_ppi_channel_t     m_ppi_channel;
//static uint32_t              m_adc_evt_counter;

//#define MMED_ADC_Q_BUFFER     8

//static nrf_saadc_value_t     m_buffer_qpool[MMED_ADC_Q_BUFFER][MMED_ADC_IN_BUFFER];
//static uint8_t mmed_adc_qcur = 0;


static void timer_handler(nrf_timer_event_t event_type, void * p_context)
{

}


static void saadc_sampling_event_init(void)
{
    ret_code_t err_code;

    err_code = nrf_drv_ppi_init();
    APP_ERROR_CHECK(err_code);

    nrf_drv_timer_config_t timer_cfg = NRF_DRV_TIMER_DEFAULT_CONFIG;
    timer_cfg.bit_width = NRF_TIMER_BIT_WIDTH_32;
    err_code = nrf_drv_timer_init(&m_timer, &timer_cfg, timer_handler);
    APP_ERROR_CHECK(err_code);

    /* setup m_timer for compare event every 4ms */
    uint32_t ticks = nrf_drv_timer_ms_to_ticks(&m_timer, 5);
    nrf_drv_timer_extended_compare(&m_timer,
                                   NRF_TIMER_CC_CHANNEL0,
                                   ticks,
                                   NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK,
                                   false);
    nrf_drv_timer_enable(&m_timer);

    uint32_t timer_compare_event_addr = nrf_drv_timer_compare_event_address_get(&m_timer,
                                        NRF_TIMER_CC_CHANNEL0);
    uint32_t saadc_sample_task_addr   = nrf_drv_saadc_sample_task_get();

    /* setup ppi channel so that timer compare event is triggering sample task in SAADC */
    err_code = nrf_drv_ppi_channel_alloc(&m_ppi_channel);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_ppi_channel_assign(m_ppi_channel,
                                          timer_compare_event_addr,
                                          saadc_sample_task_addr);
    APP_ERROR_CHECK(err_code);
}


void saadc_sampling_event_enable(bool istrue)
{
    if(istrue)
        APP_ERROR_CHECK( nrf_drv_ppi_channel_enable(m_ppi_channel));
    else
        APP_ERROR_CHECK( nrf_drv_ppi_channel_disable(m_ppi_channel));


}
/*
static void mmed_adc_evt_sceduled(void * p_event_data, uint16_t event_size)
{
    // drv_mmed_rdbytes(mmed_rdreg,mmed_rxdata,4);
    adc_drdy_evt_cb(p_event_data,true);
}
*/
static void saadc_callback(nrf_drv_saadc_evt_t const * p_event)
{
    if (p_event->type == NRF_DRV_SAADC_EVT_DONE)
    {
        ret_code_t err_code;

//       drv_mmed_test_ind(true);

        err_code = nrf_drv_saadc_buffer_convert(p_event->data.done.p_buffer, MMED_ADC_IN_BUFFER);
        APP_ERROR_CHECK(err_code);
        adc_drdy_evt_cb(p_event->data.done.p_buffer,true);
        /*
                int i;
                //     NRF_LOG_INFO("ADC event number: %d", (int)m_adc_evt_counter);

                for (i = 0; i < MMED_ADC_IN_BUFFER; i++)
                {
                    //NRF_LOG_INFO("%d", p_event->data.done.p_buffer[i]);
                    m_buffer_qpool[mmed_adc_qcur][i] = p_event->data.done.p_buffer[i];
                  //  m_buffer_qpool[mmed_adc_qcur][i] = m_buffer_qpool[mmed_adc_qcur][i];
                }
                //  m_adc_evt_counter++;

                //      drv_mmed_test_ind(false);
                err_code = app_sched_event_put((void const*)m_buffer_qpool[mmed_adc_qcur], MMED_ADC_IN_BUFFER, mmed_adc_evt_sceduled);

                //err_code = app_sched_event_put((void const*)p_event->data.done.p_buffer, MMED_ADC_IN_BUFFER, mmed_adc_evt_sceduled);
                APP_ERROR_CHECK(err_code);

                if(mmed_adc_qcur >= (MMED_ADC_Q_BUFFER-1))
                    mmed_adc_qcur = 0;
                else
                    mmed_adc_qcur++;

        */
    }
}


static void saadc_init(void)
{
    ret_code_t err_code;
    nrf_saadc_channel_config_t channel_config =
        NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(MMED_SAADC_INPUT_AIN);
    channel_config.gain = NRF_SAADC_GAIN1_2;

    channel_config.reference = NRF_SAADC_REFERENCE_VDD4;
    err_code = nrf_drv_saadc_init(NULL, saadc_callback);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_saadc_channel_init(1, &channel_config);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_saadc_buffer_convert(m_buffer_pool[0], MMED_ADC_IN_BUFFER);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_saadc_buffer_convert(m_buffer_pool[1], MMED_ADC_IN_BUFFER);
    APP_ERROR_CHECK(err_code);

}


/**
 * @brief Function for main application entry.
 */
void drv_mmed_adc_init(mmed_drdy_evt_handler_t handler  )
{
    saadc_init();
    saadc_sampling_event_init();
    // saadc_sampling_event_enable();
    adc_drdy_evt_cb  = handler;
}


/** @} */
