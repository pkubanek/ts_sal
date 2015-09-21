typedef struct m1m3_Surface_cache {
  int cppDummy;
  int syncI;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  long Raw[1024];
  float Calibrated[1024];
  char Status[256];
  int syncO;
} m1m3_Surface_cache;
