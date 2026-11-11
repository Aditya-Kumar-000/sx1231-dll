#include <stdio.h>
#include <assert.h>
#include "checksum.h"

int main(void)
{
    uint8_t good[] = {0x10, 0x20, 0xF0};
    uint8_t bad[]  = {0x10, 0x21, 0xF0};   // noise flipped one bit

    assert(sum16(good, 3) == 0xFEDF);      // your paper answer
    assert(sum16(bad, 3)  == 0xFEDE);      // the corrupted version
    assert(sum16(good, 3) != sum16(bad, 3)); // error is caught

    printf("All checksum tests passed\n");
    return 0;
}