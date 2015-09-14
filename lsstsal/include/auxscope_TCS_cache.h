typedef struct auxscope_TCS_cache {
  int cppDummy;
  int syncI;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  long Raw[200];
  float Calibrated[200];
  char Status[64];
  int syncO;
} auxscope_TCS_cache;
