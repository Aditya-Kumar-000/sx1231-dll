#include "stuff.h"
#include "config.h"


uint8_t stuff(const uint8_t *in, uint8_t len, uint8_t *out)
{
    uint8_t n = 0;                                         // how many bytes written to out

    for (uint8_t i = 0; i < len; i++) {                    // look at every input byte
        if (in[i] == FLAG_BYTE || in[i] == ESCAPE_BYTE) {  // is it 7E or AA?, ive defined the flag and esc byte in include file
            out[n++] = ESCAPE_BYTE;                        //   means “put ESCAPE_BYTE at position n, then add 1 to n”. It’s a “write and move the pen forward” move.
        }
        out[n++] = in[i];                                  // always write the byte itself
    }
    return n;                                              // new length (can be longer!)
}
// (0x41, 0xAA, 0x7E, 0x42}

uint8_t unstuff(const uint8_t *in, uint8_t len, uint8_t *out)
{
    uint8_t n = 0;                                  // writing pen position in out

    for (uint8_t i = 0; i < len; i++) {             // reading finger position in in
        if (in[i] == ESCAPE_BYTE && i + 1 < len) {  // saw 0xAA?
            i++;                                    // step reading finger over 0xAA, basically skipping the 0xAA
        }
        out[n++] = in[i];                           // write the real byte, move pen forward
    }
    return n;
}
