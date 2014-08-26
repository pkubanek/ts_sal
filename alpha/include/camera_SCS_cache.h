typedef struct camera_SCS_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  float open_profile[1024];
  float close_profile[1024];
  char algorithm[32];
  long flags;
} camera_SCS_cache;
