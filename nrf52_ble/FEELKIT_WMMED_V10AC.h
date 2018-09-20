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
#ifndef FEELKIT_WMMED_V10AC_H
#define FEELKIT_WMMED_V10AC_H



#ifndef MMED_SPI_SCK_PIN
#define MMED_SPI_SCK_PIN   19 
#endif

#ifndef MMED_SPI_MISO_PIN
#define MMED_SPI_MISO_PIN  16
#endif

#ifndef MMED_SPI_MOSI_PIN
#define MMED_SPI_MOSI_PIN   17
#endif


#ifndef MMED_SPI_SS_PIN
#define MMED_SPI_SS_PIN 20
#endif


#ifndef MMED_SPI_IRQ_PRIORITY
#define MMED_SPI_IRQ_PRIORITY 7
#endif
  

#ifndef MMED_DRDY_INT
#define MMED_DRDY_INT      15
#endif


#ifndef MMED_TEST_IND
//#define MMED_TEST_IND      26
#endif

  #ifndef MMED_SAADC_INPUT_AIN
#define MMED_SAADC_INPUT_AIN   NRF_SAADC_INPUT_AIN0
#endif

#ifndef MMED_LPCMP_INPUT_LA
#define MMED_LPCMP_INPUT_LA   NRF_LPCOMP_INPUT_4
#endif

#ifndef MMED_LPCMP_INPUT_RA
#define MMED_LPCMP_INPUT_RA   NRF_LPCOMP_INPUT_1
#endif

#ifndef MMED_LPCMP_INPUT_RT
#define MMED_LPCMP_INPUT_RT   NRF_LPCOMP_INPUT_6
#endif

#ifndef MMED_CMP_INPUT_LA
#define MMED_CMP_INPUT_LA   NRF_COMP_INPUT_4
#endif

#ifndef MMED_CMP_INPUT_RA
#define MMED_CMP_INPUT_RA   NRF_COMP_INPUT_1
#endif

#ifndef MMED_CMP_INPUT_RT
#define MMED_CMP_INPUT_RT   NRF_COMP_INPUT_6
#endif

// LEDs definitions for PCA10040
#define LEDS_NUMBER    1

#define LED_START      10
#define LED_1          10
#define LED_STOP       10

#define LEDS_ACTIVE_STATE 0

#define LEDS_INV_MASK  LEDS_MASK

#define LEDS_LIST { LED_1}

#define BSP_LED_0      LED_1

#define BUTTONS_NUMBER 1

#define BUTTON_START   18
#define BUTTON_1       18
//#define BUTTON_2       14
//#define BUTTON_3       15
//#define BUTTON_4       16
#define BUTTON_STOP    18
#define BUTTON_PULL    NRF_GPIO_PIN_PULLUP

#define BUTTONS_ACTIVE_STATE 0

//#define BUTTONS_LIST { BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4 }
#define BUTTONS_LIST { BUTTON_1 }

#define BSP_BUTTON_0   BUTTON_1
//#define BSP_BUTTON_1   BUTTON_2
//#define BSP_BUTTON_2   BUTTON_3
//#define BSP_BUTTON_3   BUTTON_4

#define RX_PIN_NUMBER  27
#define TX_PIN_NUMBER  26
//#define CTS_PIN_NUMBER 7
//#define RTS_PIN_NUMBER 5
//#define HWFC           true


#endif // PCA10040_H
