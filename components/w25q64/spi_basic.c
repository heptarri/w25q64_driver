#include "spi_basic.h"

uint8_t miso, mosi, cs, clk;

void w_cs(uint8_t bv) { gpio_set_level(cs, bv); }
void w_clk(uint8_t bv) { gpio_set_level(clk, bv); }
void w_miso(uint8_t bv) { gpio_set_level(miso, bv); }
void w_mosi(uint8_t bv) { gpio_set_level(mosi, bv); }
uint8_t r_miso(void) { return gpio_get_level(miso); }

/**
 * @brief Initialize the SPI peripheral.
 * The function will initialize the SPI bus, the SPI device which mounts the
 * wanted peripheral in proper order. The detailed procedure can be found in the
 * document of ESP-IDF.
 *
 * @param miso_pin The MISO(Master In Slave Out) pin number.
 * @param mosi_pin The MOSI(Master Out Slave In) pin number.
 * @param cs_pin The CS(Chip Select) pin number.
 * @param clk_pin The CLK(Clock) pin number.
 *
 * The detailed definition of above params can be found in the standard of SPI.
 * This initialization function only supports full-duplex SPI communication.
 */
void spi_basic_init(uint8_t miso_pin, uint8_t mosi_pin, uint8_t cs_pin,
                    uint8_t clk_pin) {
  miso = miso_pin;
  mosi = mosi_pin;
  cs = cs_pin;
  clk = clk_pin;

  gpio_config_t io_conf = {
      .mode = GPIO_MODE_OUTPUT,
      .pin_bit_mask = (1 << mosi_pin) | (1 << clk_pin) | (1 << cs_pin),
  };
  gpio_config(&io_conf);

  gpio_config_t io_conf_cs = {
      .mode = GPIO_MODE_INPUT,
      .pin_bit_mask = (1 << miso_pin),
      .pull_up_en = GPIO_PULLUP_ENABLE,
  };
  gpio_config(&io_conf_cs);

  w_cs(1);
  w_clk(0);
}

void spi_start(void) { w_cs(0); }
void spi_stop(void) { w_cs(1); }

/**
 * @brief Exchange the Rx_data and Tx_data between the master device and slave
 * device
 *
 * Refer to the SPI standard, the SPI Controller provides a data register to
 * exchange data synchronously which means the master device transfers a byte
 * while the slave device transfers back a byte. So just give the function Rx
 * and Tx address, it will transfer datas back.
 *
 * @param rx_data The pointer of address where you want to save the received
 * data. It often be a pointer of an array.
 * @param tx_data The pointer of the data you want to transmit. It often be a
 * pointer of an array.
 * @param len The bigger length of rx_data and tx_data array.
 *
 * Because of the initialization of the spi_init() function, this function only
 * can transmit data to the former selected CS pin.
 */
uint8_t spi_transfer(uint8_t bs) {
  uint8_t br = 0x00;

  for (int i = 0; i < 8; i++) {
    w_mosi(bs & (0x80 >> i));
    w_clk(1);
    if (r_miso()) {
      br |= (0x80 >> i);
    }
    w_clk(0);
  }

  return br;
}
