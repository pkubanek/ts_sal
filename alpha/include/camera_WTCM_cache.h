typedef struct camera_WTCM_cache {
  int cppDummy;
  int syncI;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  float parameters[10];
  int syncO;
} camera_WTCM_cache;
