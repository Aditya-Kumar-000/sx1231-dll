#include <stdio.h>
#include <assert.h>
#include "checksum.h"

int main(void)
{

    uint8_t good[] = {0x10, 0x20, 0xF0}; // this is the good order
    uint8_t bad[]  = {0x10, 0x21, 0xF0};   // noise flipped one bit
// format: uint16_t sum16(const uint8_t *data, uint8_t len);
    assert(sum16(good, 3) == 0xFEDF);      // your paper answer
    // basically we are passing good as data and then length = 3
    assert(sum16(bad, 3)  == 0xFEDE);      // the corrupted version
    assert(sum16(good, 3) != sum16(bad, 3)); // error is caught
    uint8_t check[] = "123456789";
    assert(crc16(check, 9) == 0x29B1); // is the official expected value if start at 0xFFFF with polynomial 0x1021 
    uint8_t a[] = {0x01, 0x02, 0x03};
    uint8_t b[] = {0x03, 0x02, 0x01};
    assert(sum16(a, 3) == sum16(b, 3));             // sum MISSES the swap
    assert(crc16(a, 3) != crc16(b, 3));             // CRC CATCHES it

    printf("All checksum tests passed\n");
    return 0;
}

/*
#######################################
on the line 19 the sum16 fails because of this exact pattern issue the data was same but jumbled and hence the 
sum was same therefore was not caught by SUM16
*/