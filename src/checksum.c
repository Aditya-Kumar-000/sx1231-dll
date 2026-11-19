#include "checksum.h"

uint16_t sum16(const uint8_t *data, uint8_t len)
{
    uint16_t sum = 0;
    for (uint8_t i = 0; i < len; i++) {
        sum = sum + data[i];         
    }
    return ~sum;   
}         

uint16_t crc16(const uint8_t *data, uint8_t len)
{
    uint16_t crc = 0xFFFF;                        // starting value, we agreed in spec
    for (uint8_t i = 0; i < len; i++) {           // for every byt
        crc ^= (uint16_t)data[i] << 8;            // RULE 1: feed it in into the TOP half
        for (uint8_t bit = 0; bit < 8; bit++) {   // RULE 2: step 8  per byte
            if (crc & 0x8000)                     //   if the top bit is 1 then
                crc = (crc << 1) ^ 0x1021;        //   shift + XOR pattern (XOR Pattern = 0x1021 agreed in the spec)
            else
                crc = crc << 1;                   //   shift only if the top bit is not 1
        }
    }
    return crc;                                   // RULE 3: the box is the CRC
}

