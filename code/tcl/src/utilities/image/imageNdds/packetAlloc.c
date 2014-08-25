#include <NDDS.h>
#include <ImageHeader.h>
#include <ImagePacket.h>
#include "imageNdds.h"

/* Fix the pointers in a block allocated ImagePacket */
void
ImagePacketBlockFixup (ImagePacket h)
{
    h->line_data.line_data_val = (char *)h + sizeof (struct ImagePacketStruct);
}

/* Copy from one block allocated packet to another */
void
ImagePacketBlockCopy (ImagePacket to, const ImagePacket from)
{
    if (!to || !from) return;
    if (to == from) return;		/* its the same */
    memcpy (to, from, IMAGE_PACKET_BLOCK_SIZE);
    ImagePacketBlockFixup (to);
}

/* allocate a ImagePacket in a single block */
ImagePacket
ImagePacketBlockAlloc (void)
{
    ImagePacket h;

    h = (ImagePacket)calloc(1, IMAGE_PACKET_BLOCK_SIZE);
    if (!h) return NULL;
    h->line_data.line_data_len = IMAGE_PACKET_BLOCK_SIZE;
    ImagePacketBlockFixup (h);
    return h;
}
