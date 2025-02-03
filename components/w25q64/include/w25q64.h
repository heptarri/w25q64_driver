#ifndef __W25Q64_H
#define __W25Q64_h

#include <stdio.h>

#include "spi_basic.h"
#include "w25q64_ins.h"

typedef struct {
  uint8_t mosi_pin, miso_pin, clk_pin, cs_pin;
} W25Q64_t;

void W25Q64_init(W25Q64_t *inf);
void W25Q64_readID(uint8_t *MID, uint16_t *DID);

void W25Q64_PageProgram(uint32_t addr, uint8_t *dr, uint16_t len);
void W25Q64_SectorErase(uint32_t addr);
void W25Q64_ReadData(uint32_t addr, uint8_t *dr, uint32_t len);

#endif  // !__W25Q64_H
