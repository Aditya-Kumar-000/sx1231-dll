#include <stdio.h>
#include <assert.h>
#include "config.h"

int main(void)
{
    assert(MAX_PAYLOAD * MAX_FRAGMENTS == 92);    // biggest packet the DLL accepts
    assert(MAX_PAYLOAD * MAX_FRAGMENTS >= 83);    // still covers NET's biggest packet
    assert(BIT_FRAG_INDEX + 1 < BIT_CRC_ENABLE);  // Frag_Index (2 bits) doesn't overlap CRC bit

    printf("All config tests passed\n");
    return 0;
}