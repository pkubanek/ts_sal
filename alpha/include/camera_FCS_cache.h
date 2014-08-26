typedef struct camera_FCS_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  float motion_profile[60*40];
  char algorithm[32];
  long flags;
} camera_FCS_cache;
