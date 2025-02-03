#include "w25q64.h"

void W25Q64_init(W25Q64_t *inf) {
  spi_basic_init(inf->miso_pin, inf->mosi_pin, inf->cs_pin, inf->clk_pin);
}

void W25Q64_readID(uint8_t *MID, uint16_t *DID) {
  spi_start();

  spi_transfer(W25Q64_JEDEC_ID);
  *MID = spi_transfer(W25Q64_DUMMY_BYTE);

  *DID = spi_transfer(W25Q64_DUMMY_BYTE);
  *DID <<= 8;
  *DID |= spi_transfer(W25Q64_DUMMY_BYTE);

  spi_stop();
}

void W25Q64_WriteEnable(void) {
  spi_start();

  spi_transfer(W25Q64_WRITE_ENABLE);

  spi_stop();
}

void W25Q64_WaitBusy(void) {
  uint32_t timeout = 1000000;
  spi_start();

  spi_transfer(W25Q64_READ_STATUS_REGISTER_1);
  while ((spi_transfer(W25Q64_DUMMY_BYTE) & 0x01) == 0x01) {
    --timeout;
    if (timeout == 0) {
      break;
    }
  }

  spi_stop();
}

void W25Q64_PageProgram(uint32_t addr, uint8_t *dr, uint16_t len) {
  W25Q64_WriteEnable();

  spi_start();

  spi_transfer(W25Q64_PAGE_PROGRAM);
  spi_transfer(addr >> 16);
  spi_transfer(addr >> 8);
  spi_transfer(addr);

  for (uint16_t i = 0; i < len; i++) {
    spi_transfer(dr[i]);
  }

  spi_stop();

  W25Q64_WaitBusy();
}

void W25Q64_SectorErase(uint32_t addr) {
  W25Q64_WriteEnable();

  spi_start();

  spi_transfer(W25Q64_SECTOR_ERASE_4KB);
  spi_transfer(addr >> 16);
  spi_transfer(addr >> 8);
  spi_transfer(addr);

  spi_stop();

  W25Q64_WaitBusy();
}

void W25Q64_ReadData(uint32_t addr, uint8_t *dr, uint32_t len) {
  spi_start();

  spi_transfer(W25Q64_READ_DATA);
  spi_transfer(addr >> 16);
  spi_transfer(addr >> 8);
  spi_transfer(addr);

  for (uint32_t i = 0; i < len; i++) {
    dr[i] = spi_transfer(W25Q64_DUMMY_BYTE);
  }

  spi_stop();
}