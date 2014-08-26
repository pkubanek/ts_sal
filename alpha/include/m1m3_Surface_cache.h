typedef struct m1m3_Surface_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  long Raw[1024];
  float Calibrated[1024];
} m1m3_Surface_cache;
