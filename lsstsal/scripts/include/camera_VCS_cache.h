typedef struct camera_VCS_cache {
  int cppDummy;
  int syncI;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  float control[10];
  float pressure[10];
  int syncO;
} camera_VCS_cache;
