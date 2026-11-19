#include <stdio.h>
#include <assert.h>
#include <string.h>
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

    // Reassembly tests: a 50-byte packet with values 0, 1, 2 ... 49
    uint8_t pkt[50];
    for (uint8_t i = 0; i < 50; i++) pkt[i] = i;
    reasm_t r;
    reasm_reset(&r);

    // Case 1: idx 0, 1, 2 in order -> returns 0, 0, then 1; r.len == 50; r.buf matches pkt
    assert(reasm_add(&r, 0, 1, pkt + 0,  23) == 0);
    assert(reasm_add(&r, 1, 1, pkt + 23, 23) == 0);
    assert(reasm_add(&r, 2, 0, pkt + 46, 4)  == 1);
    assert(r.len == 50);
    assert(memcmp(r.buf, pkt, 50) == 0);

    // Case 2: add idx 0, idx 1, then a NEW idx 0 -> old packet wiped, r.len == 23
    assert(reasm_add(&r, 0, 1, pkt + 0,  23) == 0);
    assert(reasm_add(&r, 1, 1, pkt + 23, 23) == 0);
    assert(reasm_add(&r, 0, 1, pkt + 0,  23) == 0);
    assert(r.len == 23);

    // Case 3: add idx 0, then idx 2 (missing idx 1) -> returns 0 and r.len == 0
    assert(reasm_add(&r, 0, 1, pkt + 0,  23) == 0);
    assert(reasm_add(&r, 2, 0, pkt + 46, 4)  == 0);
    assert(r.len == 0);

    // Case 4: fresh reset, then add idx 1 first -> returns 0 and r.len == 0
    reasm_reset(&r);
    assert(reasm_add(&r, 1, 1, pkt + 23, 23) == 0);
    assert(r.len == 0);

    printf("All frag tests passed\n");
    return 0;
}