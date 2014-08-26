#define camera_BEE_biases_revCode "5f1b3775bfabf2d7f4bba708625aea62"
typedef struct camera_BEE_biases_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  long reset[201];
  long operate[201];
  long substrate[201];
} camera_BEE_biases_cache;
