#ifndef __SPI_BASIC_H

#define __SPI_BASIC_H

#include <stdio.h>

#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"

extern uint8_t miso, mosi, cs, clk;

void spi_basic_init(uint8_t miso_pin, uint8_t mosi_pin, uint8_t cs_pin,
                    uint8_t clk_pin);
uint8_t spi_transfer(uint8_t bs);

void spi_start(void);
void spi_stop(void);

#endif