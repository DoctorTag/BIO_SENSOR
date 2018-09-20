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
#include "nrf_drv_lpcomp.h"
#include "nrf_drv_comp.h"
//#include "nrf_drv_ppi.h"
#include "nrf_drv_gpiote.h"
#include "boards.h"
#include "app_error.h"
#include "nrf_delay.h"
#include "app_util_platform.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_drv_power.h"

//#include "app_scheduler.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "drv_mmed.h"
#include "drv_mmed_cmp.h"

#include "app_timer.h"

#include "nrf_assert.h"

#define              MMED_CMP_DETECTION_DELAY             800
APP_TIMER_DEF(comp_detection_delay_timer_id);  /**< Polling timer id. */


APP_TIMER_DEF(lpcomp_detection_delay_timer_id);  /**< Polling timer id. */

//#define MMED_CMP_TEST
#define MMED_CMP_TEST_IND  29


static bool lpcomp_result,comp_result;


#if defined MMED_CMP_TEST_IND

void drv_mmed_cmp_ind(bool isset)
{
    if(isset)
        nrf_drv_gpiote_out_set(MMED_CMP_TEST_IND);

    else
        nrf_drv_gpiote_out_clear(MMED_CMP_TEST_IND);

}

#endif

static void lpcomp_detection_delay_timeout_handler(void * p_context)
{
    if(nrf_drv_lpcomp_sample() == 0)
    {
        if(lpcomp_result == false)
        {
#if defined MMED_CMP_TEST_IND

            drv_mmed_cmp_ind(false);

#endif
        }
    }
    else
    {
        if(lpcomp_result)
        {
#if defined MMED_CMP_TEST_IND

            drv_mmed_cmp_ind(true);

#endif
        }
    }
}

static void comp_detection_delay_timeout_handler(void * p_context)
{
    if(nrf_drv_comp_sample() == 0)
    {
        if(comp_result == false)
        {

        }
    }
    else
    {
        if(comp_result)
        {

        }
    }
}

/**
 * @brief Dummy handler for COMP events.
 *
 * @param[in] event         COMP event.
 */
static void comp_event_handler(nrf_comp_event_t event)
{
    if (event == NRF_COMP_EVENT_CROSS)
    {

        if(nrf_drv_comp_sample() == 0)
            comp_result = false;
        else
            comp_result = true;
        app_timer_stop(comp_detection_delay_timer_id);
        app_timer_start(comp_detection_delay_timer_id, MMED_CMP_DETECTION_DELAY, NULL);



    }
}

/**
 * @brief Function for initializing COMP module in relaxation oscillator mode.
 *
 * @note The frequency of the oscillator depends on threshold voltages, current source and capacitance of pad and can be calculated as f_OSC = I_SOURCE / (2CÂ·(VUP-VDOWN) ).
 *
 * @retval NRF_ERROR_INTERNAL                If there were error while initializing COMP driver.
 * @retval NRF_SUCCESS                       If the COMP driver initialization was successful.
 */
static ret_code_t comp_init(void)
{
    ret_code_t err_code;
    nrf_drv_comp_config_t m_comp_config = NRF_DRV_COMP_DEFAULT_CONFIG(MMED_CMP_INPUT_RA);

    /* Workaround for Errata 12 "COMP: Reference ladder is not correctly calibrated" found at the Errata document
       for your device located at https://infocenter.nordicsemi.com/ */
    *(volatile uint32_t *)0x40013540 = (*(volatile uint32_t *)0x10000324 & 0x00001F00) >> 8;

    m_comp_config.isource = NRF_COMP_ISOURCE_Ien10uA;

    err_code = nrf_drv_comp_init(&m_comp_config, comp_event_handler);
    if (err_code != NRF_SUCCESS)
    {
        return NRF_ERROR_INTERNAL;
    }
    return app_timer_create(&comp_detection_delay_timer_id,
                            APP_TIMER_MODE_SINGLE_SHOT,
                            comp_detection_delay_timeout_handler);
    //return NRF_SUCCESS;
}


/**
 * @brief LPCOMP event handler is called when LPCOMP detects voltage drop.
 *
 * This function is called from interrupt context so it is very important
 * to return quickly. Don't put busy loops or any other CPU intensive actions here.
 * It is also not allowed to call soft device functions from it (if LPCOMP IRQ
 * priority is set to APP_IRQ_PRIORITY_HIGH).
 */
static void lpcomp_event_handler(nrf_lpcomp_event_t event)
{
    // static bool test=true;
    /*  if (event == NRF_LPCOMP_EVENT_DOWN)
      {
    #if defined MMED_CMP_TEST_IND

          drv_mmed_cmp_ind(false);

    #endif
      }

      if (event == NRF_LPCOMP_EVENT_UP)
      {
    #if defined MMED_CMP_TEST_IND

          drv_mmed_cmp_ind(true);

    #endif */
    if (event == NRF_LPCOMP_EVENT_CROSS)
    {

        if(nrf_drv_lpcomp_sample() == 0)
            lpcomp_result = false;
        else
            lpcomp_result = true;
        app_timer_stop(lpcomp_detection_delay_timer_id);
        app_timer_start(lpcomp_detection_delay_timer_id, MMED_CMP_DETECTION_DELAY, NULL);



    }
}


/**
 * @brief Initialize LPCOMP driver.
 */
static ret_code_t  lpcomp_init(void)
{
    uint32_t                err_code;

    nrf_drv_lpcomp_config_t config = NRF_DRV_LPCOMP_DEFAULT_CONFIG;
    config.input = MMED_LPCMP_INPUT_LA;
    // initialize LPCOMP driver, from this point LPCOMP will be active and provided
    // event handler will be executed when defined action is detected
    err_code = nrf_drv_lpcomp_init(&config, lpcomp_event_handler);
    APP_ERROR_CHECK(err_code);
    nrf_drv_lpcomp_enable();

#if defined MMED_CMP_TEST_IND
    nrf_drv_gpiote_out_config_t out_config = GPIOTE_CONFIG_OUT_SIMPLE(true);
    err_code = nrf_drv_gpiote_out_init(MMED_CMP_TEST_IND, &out_config);
    APP_ERROR_CHECK(err_code);
#endif

    return app_timer_create(&lpcomp_detection_delay_timer_id,
                            APP_TIMER_MODE_SINGLE_SHOT,
                            lpcomp_detection_delay_timeout_handler);

//return NRF_SUCCESS;
}

/**
 * @brief Function for main application entry.
 */
void drv_mmed_cmp_init(void)
{
    lpcomp_init();
    comp_init();

    //  adc_drdy_evt_cb  = handler;
}


/** @} */
