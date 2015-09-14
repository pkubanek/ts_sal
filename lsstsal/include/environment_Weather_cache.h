typedef struct environment_Weather_cache {
  int cppDummy;
  int syncI;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  long Raw[128];
  float Calibrated[256];
  char Status[128];
  int syncO;
} environment_Weather_cache;
