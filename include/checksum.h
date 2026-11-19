#ifndef CHECKSUM_H
#define CHECKSUM_H

#include <stdint.h>

uint16_t sum16(const uint8_t *data, uint8_t len);

uint16_t crc16(const uint8_t *data, uint8_t len); // this is the optional CRC16 

#endif