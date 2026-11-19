#ifndef FRAG_H
#define FRAG_H

#include <stdint.h>

typedef struct {
    uint8_t buf[92];       // the packet being rebuilt
    uint8_t len;           // how many bytes are in it so far
    uint8_t expect;        // which Frag_Index should arrive next
} reasm_t;

uint8_t frag_split(uint8_t len, uint8_t chunk_len[]);
void    reasm_reset(reasm_t *r);
uint8_t reasm_add(reasm_t *r, uint8_t idx, uint8_t more,
                  const uint8_t *data, uint8_t len);

#endif
