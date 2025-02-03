#ifndef __SPI_BASIC_H

#define __SPI_BASIC_H

#define MISO_PIN 16
#define MOSI_PIN 17
#define CS_PIN 15
#define CLK_PIN 5

#include <stdio.h>

#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "esp_err.h"
#include "esp_log.h"
extern spi_device_handle_t my_spi;

void spi_basic_init(void);
void spi_transfer(uint8_t *rx_data, uint8_t *tx_data, uint8_t len);

#endif