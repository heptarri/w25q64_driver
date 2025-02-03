#ifndef __W25Q64_H
#define __W25Q64_h

#include <stdio.h>

#include "spi_basic.h"
#include "w25q64_ins.h"

typedef struct {
  uint8_t mosi_pin, miso_pin, clk_pin, cs_pin;
} W25Q64_t;

void W25Q64_init(W25Q64_t *inf);
void W25Q64_readID(uint8_t *MID, uint8_t *DID);

#endif  // !__W25Q64_H
