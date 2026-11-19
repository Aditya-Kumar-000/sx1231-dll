#include <stdio.h>
#include <assert.h>
#include "frame.h"

int main(void)
{
    // (a) pack the hook example -> must be 0x002A
    control_t c = {0};
    c.seq        = 1;
    c.more_frags = 1;
    c.frag_index = 2;
    assert(control_pack(c) == 0x002A);

    // (b) unpack 0x002A
    control_t u = control_unpack(0x002A);
    assert(u.seq == 1);
    assert(u.more_frags == 1);
    assert(u.frag_index == 2);

    // (c) round trip: pack then unpack and check every field
    control_t orig = {
        .frame_type = 1,
        .seq        = 1,
        .ack        = 1,
        .more_frags = 0,
        .frag_index = 3,
        .crc_enable = 1
    };
    control_t back = control_unpack(control_pack(orig));
    assert(back.frame_type == orig.frame_type);
    assert(back.seq        == orig.seq);
    assert(back.ack        == orig.ack);
    assert(back.more_frags == orig.more_frags);
    assert(back.frag_index == orig.frag_index);
    assert(back.crc_enable == orig.crc_enable);

    printf("All frame tests passed\n");
    return 0;
}
