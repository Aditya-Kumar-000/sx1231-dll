// basically we are shifting each of the frames into its respective bits slots

#include "frame.h"
#include "config.h"

uint16_t control_pack(control_t c)
{
    uint16_t raw = 0;                                        // start with all bits 0
    raw |= (uint16_t)(c.frame_type & 0x1) << BIT_FRAME_TYPE; // 1 bit → slot 0
    raw |= (uint16_t)(c.seq        & 0x1) << BIT_SEQ;        // 1 bit → slot 1
    raw |= (uint16_t)(c.ack        & 0x1) << BIT_ACK;        // 1 bit → slot 2
    raw |= (uint16_t)(c.more_frags & 0x1) << BIT_MORE_FRAGS; // 1 bit → slot 3
    raw |= (uint16_t)(c.frag_index & 0x3) << BIT_FRAG_INDEX; // 2 bits → slots 4–5
    raw |= (uint16_t)(c.crc_enable & 0x1) << BIT_CRC_ENABLE; // 1 bit → slot 6
                                                             // bits 7–15 stay 0 (reserved)
    return raw;
}



control_t control_unpack(uint16_t raw)
{
    control_t c;
    c.seq = (raw >> BIT_SEQ) & 0x1;     // ← here's one done for you
    // … do the other five the same way (Frag_Index uses 0x3)
    c.frame_type = (raw >> BIT_FRAME_TYPE) & 0x1;
    c.ack = (raw >> BIT_ACK) & 0x1;
    c.more_frags = (raw >> BIT_MORE_FRAGS) & 0x1;
    c.frag_index = (raw >> BIT_FRAG_INDEX) & 0x3;
    c.crc_enable = (raw >> BIT_CRC_ENABLE) & 0x1;
    return c;
}