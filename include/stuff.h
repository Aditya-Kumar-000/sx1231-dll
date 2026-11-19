#ifndef STUFF_H
#define STUFF_H

#include <stdint.h>

uint8_t stuff(const uint8_t *in, uint8_t len, uint8_t *out);
uint8_t unstuff(const uint8_t *in, uint8_t len, uint8_t *out);

#endif