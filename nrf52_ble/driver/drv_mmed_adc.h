#ifndef DRV_MMED_ADC_H
#define DRV_MMED_ADC_H

#define MMED_ADC_IN_BUFFER     5

/**
 * @brief Function for main application entry.
 */
void drv_mmed_adc_init(mmed_drdy_evt_handler_t handler  );

void saadc_sampling_event_enable(bool istrue);
#endif
/** @} */
