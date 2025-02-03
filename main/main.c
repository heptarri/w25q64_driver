#include "w25q64.h"

#define MISO_PIN 16
#define MOSI_PIN 17
#define CS_PIN 15
#define CLK_PIN 5

void app_main(void) {
  W25Q64_t dev = {
      .clk_pin = CLK_PIN,
      .cs_pin = CS_PIN,
      .miso_pin = MISO_PIN,
      .mosi_pin = MOSI_PIN,
  };

  W25Q64_init(&dev);

  uint8_t MID;
  uint16_t DID;
  W25Q64_readID(&MID, &DID);

  ESP_LOGI("main.c", "MID: 0x%02X, DID: %04X", MID, DID);

  uint8_t tx[] = {0x07, 0x27, 0x77}, rx[3];
  W25Q64_SectorErase(0x000000);
  W25Q64_PageProgram(0x000000, tx, 3);
  W25Q64_ReadData(0x000000, rx, 3);

  ESP_LOGI("main.c", "Data: 0x%02X 0x%02X 0x%02X", rx[0], rx[1], rx[2]);
}