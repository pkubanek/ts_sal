typedef struct camera_CALSYS_cache {
  int cppDummy;
  int syncI;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  float profile[1024];
  int syncO;
} camera_CALSYS_cache;
