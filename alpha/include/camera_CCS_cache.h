typedef struct camera_CCS_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  long expHist[1024];
  long flags[10];
} camera_CCS_cache;
