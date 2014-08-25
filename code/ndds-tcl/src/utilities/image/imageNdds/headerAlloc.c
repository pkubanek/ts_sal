#include <NDDS.h>
#include <ImageHeader.h>
#include <ImagePacket.h>
#include "imageNdds.h"

/* Fix the pointers in a block allocated ImageHeader */
void
ImageHeaderBlockFixup (ImageHeader h)
{
    h->name = ((char *)h) + sizeof (struct ImageHeaderStruct);
    h->type = h->name +64;
    h->date = h->type +64;
}

/* Copy from one block allocated header to another */
void
ImageHeaderBlockCopy (ImageHeader to, const ImageHeader from)
{
    if (!to || !from) return;
    if (to == from) return;		/* its the same */
    memcpy (to, from, IMAGE_HEADER_BLOCK_SIZE);
    ImageHeaderBlockFixup (to);
}

/* allocate a ImageHeader in a single block */
ImageHeader
ImageHeaderBlockAlloc (void)
{
    ImageHeader h;

    h = (ImageHeader)calloc(1, IMAGE_HEADER_BLOCK_SIZE);
    if (!h) return NULL;
    ImageHeaderBlockFixup (h);
    return h;
}
