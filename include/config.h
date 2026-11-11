#ifndef CONFIG_H 
// if already not included ifndef
#define CONFIG_H
// Frame
#define FLAG_BYTE        0x7E
#define ESCAPE_BYTE      0xAA
#define MAX_PAYLOAD      23      /* NET bytes per frame */
#define MAX_FRAGMENTS    4
#define BROADCAST_ADDR   0x00

// Control bits
#define BIT_FRAME_TYPE   0
#define BIT_SEQ          1
#define BIT_ACK          2
#define BIT_MORE_FRAGS   3
#define BIT_FRAG_INDEX   4       /* uses bits 4 and 5 */
#define BIT_CRC_ENABLE   6

// ARQ
#define ACK_TIMEOUT_MS   150
#define MAX_RETRIES      3
//mac
#define CSMA_P_PERCENT   80      /* TBC: standard or local? */
#define CSMA_BUSY_DBM    (-90)   /* TBC */

//radio
#define RADIO_BAND_MHZ   868

#endif