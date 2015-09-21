typedef struct camera_SDS_cache {
  int cppDummy;
  int syncI;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  long flags[20];
  float current[80];
  int syncO;
} camera_SDS_cache;
