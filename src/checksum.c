#include "checksum.h"

uint16_t sum16(const uint8_t *data, uint8_t len)
{
    uint16_t sum = 0;

    for (uint8_t i = 0; i < len; i++) {
        sum = sum + data[i];         
    }
    return ~sum;   
}         