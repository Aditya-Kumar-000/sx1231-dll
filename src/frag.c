#include <string.h>
#include "frag.h"
#include "config.h"

uint8_t frag_split(uint8_t len, uint8_t chunk_len[])
{
    if (len == 0 || len > MAX_PAYLOAD * MAX_FRAGMENTS)
        return 0;

    uint8_t remaining = len;
    uint8_t chunk;
    uint8_t count = 0;                 //  NEW: counts how many chunks we've made

    while (remaining > 0)
    {
        if (remaining > MAX_PAYLOAD) // all defined in config.h
        {
            chunk = MAX_PAYLOAD;
            remaining = remaining - MAX_PAYLOAD;
        }
        else
        {
            chunk = remaining;
            remaining = 0;
        }

        chunk_len[count] = chunk;      //  write down this chunk and then store it in list
        count++;                       //        …and move to the next slot
    }
    return count;                      // how many chunks (0 = rejected)
}


void reasm_reset(reasm_t *r)
{
    r->len = 0;
    r->expect = 0;
}

uint8_t reasm_add(reasm_t *r, uint8_t idx, uint8_t more,
                  const uint8_t *data, uint8_t len)
{
    if (idx == 0)
        reasm_reset(r);

    if (idx != r->expect || r->len + len > MAX_PAYLOAD * MAX_FRAGMENTS) {
        reasm_reset(r);
        return 0;
    }

    memcpy(&r->buf[r->len], data, len);
    r->len += len;
    r->expect++;

    return (more == 0);   // 1 if last fragment, 0 if more are coming
}