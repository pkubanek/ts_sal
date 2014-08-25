typedef struct environment_TC_cache {
  int cppDummy;
  int syncI;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  long Raw[64];
  float Calibrated[64];
  char Health[64];
  int syncO;
} environment_TC_cache;
