#include "spi_basic.h"

spi_device_handle_t my_spi = NULL;

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
  // Configure the SPI bus
  spi_bus_config_t bus_conf = {
      .miso_io_num = miso_pin,
      .mosi_io_num = mosi_pin,
      .sclk_io_num = clk_pin,
      .quadhd_io_num = -1,
      .quadwp_io_num = -1,
  };

  // Configure the SPI interfaces
  spi_device_interface_config_t dev_conf = {
      .clock_speed_hz = 10000000,
      .mode = 0,
      .spics_io_num = cs_pin,
      .queue_size = 7,
      .pre_cb = NULL,
  };

  esp_err_t ret;

  // Initialize the SPI bus
  ret = spi_bus_initialize(SPI2_HOST, &bus_conf, SPI_DMA_CH_AUTO);
  if (ret != ESP_OK) {
    ESP_LOGE("spi_basic.c", "Failed to initialize SPI bus: %s",
             esp_err_to_name(ret));
    return;
  }

  // Add devices to SPI bus
  ret = spi_bus_add_device(SPI2_HOST, &dev_conf, &my_spi);
  if (ret != ESP_OK) {
    ESP_LOGE("spi_basic.c", "Failed to add SPI device: %s",
             esp_err_to_name(ret));

    spi_bus_free(SPI2_HOST);  // Free the SPI bus
    return;
  }
}

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
void spi_transfer(uint8_t *rx_data, uint8_t *tx_data, uint8_t len) {
  spi_transaction_t spt = {
      .length = len * 8,
      .tx_buffer = tx_data,
      .rx_buffer = rx_data,
  };
  spi_device_transmit(my_spi, &spt);
}

/**
 * @brief Send data to SPI devices.
 *
 * @param tx_data The pointer of the data you want to transmit. It often be a
 * pointer of an array.
 * @param len The length of tx_data array.
 *
 * Because of the initialization of the spi_init() function, this function only
 * can transmit data to the former selected CS pin.
 */
void spi_send(uint8_t *tx_data, uint8_t len) {
  spi_transaction_t spt = {
      .length = len * 8,
      .tx_buffer = tx_data,
      .rx_buffer = NULL,
  };
  spi_device_transmit(my_spi, &spt);
}

/**
 * @brief Receive data to SPI devices.
 *
 * @param rx_data The pointer of address where you want to save the received
 * data. It often be a pointer of an array.
 * @param len The length of rx_data array.
 *
 * Because of the initialization of the spi_init() function, this function only
 * can transmit data to the former selected CS pin.
 */
void spi_receive(uint8_t *rx_data, uint8_t len) {
  spi_transaction_t spt = {
      .length = len * 8,
      .tx_buffer = NULL,
      .rx_buffer = rx_data,
  };
  spi_device_transmit(my_spi, &spt);
}