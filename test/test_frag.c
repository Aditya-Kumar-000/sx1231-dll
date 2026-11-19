#include <stdio.h>
#include <assert.h>
#include "frag.h"
#include "frag.h"
#include "config.h"

int main(void)
{
    uint8_t chunks[4];   // max 4 fragments

    // Example 1: valid packet (len = 50 -> 3 chunks: 23, 23, 4)
    assert(frag_split(50, chunks) == 3);
    assert(chunks[0] == 23 && chunks[1] == 23 && chunks[2] == 4);

    // Example 2: rejected packet (len = 0 -> returns 0, no chunks to check)
    assert(frag_split(0, chunks) == 0);

    // Now add the remaining rows using the same pattern:
    // len = 1  -> returns 1, chunks[0] == 1
    assert(frag_split(1, chunks) == 1);
    assert(chunks[0] == 1);
    // len = 23 -> returns 1, chunks[0] == 23
    assert(frag_split(23, chunks) == 1);
    assert(chunks[0] == 23);
    // len = 24 -> returns 2, chunks: 23, 1    
    assert(frag_split(24, chunks) == 2);
    assert(chunks[0] == 23 && chunks[1] == 1);
    // len = 83 -> returns 4, chunks: 23, 23, 23, 14
    assert(frag_split(83, chunks) == 4);
    assert(chunks[0] == 23 && chunks[1] == 23 && chunks[2] == 23 && chunks[3] == 14);
    // len = 92 -> returns 4, chunks: 23, 23, 23, 23
    assert(frag_split(92, chunks) == 4);
    assert(chunks[0] == 23 && chunks[1] == 23 && chunks[2] == 23 && chunks[3] == 23);
    // len = 93 -> returns 0
    assert(frag_split(93, chunks) == 0);
    

    printf("All frag tests passed\n");
    return 0;
}