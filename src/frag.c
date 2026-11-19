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