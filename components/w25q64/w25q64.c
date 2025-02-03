#include "w25q64.h"

void W25Q64_init(W25Q64_t *inf) {
  spi_basic_init(inf->miso_pin, inf->mosi_pin, inf->cs_pin, inf->clk_pin);
}

void W25Q64_readID(uint8_t *MID, uint8_t *DID) {
  uint8_t data[4];
  data[0] = W25Q64_JEDEC_ID;

  spi_transfer(data, data, 4);

  *MID = data[1];
  *DID = data[2];
  *DID <<= 8;
  *DID |= data[3];
}

void W25Q64_WriteEnable(void) {
  uint8_t data[1] = {W25Q64_WRITE_ENABLE};
  spi_send(data, 1);
}

void W25Q64_WaitBusy(void) {
  uint32_t timeout = 10000;

  uint8_t data[2];
  data[0] = W25Q64_READ_STATUS_REGISTER_1;

  for (;;) {
    spi_transfer(data, data, 2);
    if ((data[1] & 0x01) == 0x01) {
      --timeout;
      if (timeout == 0) break;
    } else {
      break;
    }
  }
}