#ifndef FRAME_H
#define FRAME_H

#include <stdint.h>

typedef struct {
    uint8_t frame_type;
    uint8_t seq;
    uint8_t ack;
    uint8_t more_frags;
    uint8_t frag_index;
    uint8_t crc_enable;
} control_t;

uint16_t  control_pack(control_t c);
control_t control_unpack(uint16_t raw);

#endif