#ifndef DRV_MMED_SPI_H
#define DRV_MMED_SPI_H

void mmed_spi_init (void);

uint8_t mmed_spi_read( uint8_t reg);

void mmed_spi_write( uint8_t reg,uint8_t data);

void mmed_spi_uninit (void);


#endif

