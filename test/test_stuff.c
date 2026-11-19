#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "stuff.h"

int main(void)
{
    uint8_t in[]  = {0x41, 0x7E, 0x42};
    uint8_t out[10];
    uint8_t back[10];

    uint8_t n = stuff(in, 3, out);
    assert(n == 4);
    assert(out[1] == 0xAA && out[2] == 0x7E);       // 7E got escaped

    // YOUR TESTS:
    // (a) unstuff(out, n, back) gives length 3 and back matches in   → use memcmp(back, in, 3) == 0
    uint8_t m = unstuff(out, n, back);
    assert(m == 3);
    assert(memcmp(back, in, 3) == 0);
    
    // (b) a single 0xAA input stuffs to AA AA (length 2)
    uint8_t aa_in[] = {0xAA};
    uint8_t aa_out[2];
    assert(stuff(aa_in, 1, aa_out) == 2);
    assert(aa_out[0] == 0xAA && aa_out[1] == 0xAA);

    // (c) 30 bytes all 0x7E stuff to 60 bytes   (worst case from our standard!)
    uint8_t worst_in[30];
    uint8_t worst_out[60];
    memset(worst_in, 0x7E, 30); // A shortcut that fills all 30 slots of worst_in with 0x7E without typing {0x7E, 0x7E, ...} 30 times.
    assert(stuff(worst_in, 30, worst_out) == 60);

    
    printf("All stuffing tests passed\n");
    return 0;
}