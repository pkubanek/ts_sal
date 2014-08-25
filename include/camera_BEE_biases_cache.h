typedef struct camera_BEE_biases_cache {
  int cppDummy;
  int syncI;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  long reset[201];
  long operate[201];
  long substrate[201];
  int syncO;
} camera_BEE_biases_cache;
