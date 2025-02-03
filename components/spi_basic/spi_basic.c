#include "spi_basic.h"

spi_device_handle_t my_spi = NULL;

void spi_basic_init(void) {
  gpio_config_t io_conf = {
      .mode = GPIO_MODE_OUTPUT,
      .pin_bit_mask = (1 << CS_PIN),
  };
  gpio_config(&io_conf);

  gpio_set_level(CS_PIN, 1);

  esp_err_t ret;

  // 配置 SPI 总线
  spi_bus_config_t bus_conf = {
      .miso_io_num = MISO_PIN,
      .mosi_io_num = MOSI_PIN,
      .sclk_io_num = CLK_PIN,
      .quadhd_io_num = -1,
      .quadwp_io_num = -1,
  };

  // 配置 SPI 设备接口
  spi_device_interface_config_t dev_conf = {
      .clock_speed_hz = 10000000,
      .mode = 0,
      .spics_io_num = CS_PIN,
      .queue_size = 7,
      .pre_cb = NULL,
  };

  // 初始化 SPI 总线
  ret = spi_bus_initialize(SPI2_HOST, &bus_conf, SPI_DMA_CH_AUTO);
  if (ret != ESP_OK) {
    ESP_LOGE("spi_basic.c", "Failed to initialize SPI bus: %s",
             esp_err_to_name(ret));
    return;
  }

  // 添加 SPI 设备
  ret = spi_bus_add_device(SPI2_HOST, &dev_conf, &my_spi);
  if (ret != ESP_OK) {
    ESP_LOGE("spi_basic.c", "Failed to add SPI device: %s",
             esp_err_to_name(ret));
    spi_bus_free(SPI2_HOST);  // 释放 SPI 总线
    return;
  }
}

void spi_transfer(uint8_t *rx_data, uint8_t *tx_data, uint8_t len) {
  spi_transaction_t spt = {
      .length = len * 8,
      .tx_buffer = tx_data,
      .rx_buffer = rx_data,
  };
  spi_device_transmit(my_spi, &spt);
}