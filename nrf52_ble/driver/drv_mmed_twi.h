#ifndef DRV_MMED_TWI_H
#define DRV_MMED_TWI_H

void mmed_twi_init (void);

ret_code_t mmed_twi_write(uint8_t *pdata,uint8_t len);

ret_code_t mmed_twi_read(uint8_t reg,uint8_t *p_data,uint8_t len);

void mmed_twi_uninit (void);

#endif
