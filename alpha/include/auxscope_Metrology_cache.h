typedef struct auxscope_Metrology_cache {
  int cppDummy;
  int syncI;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  long Raw[16];
  float Calibrated[16];
  char Limits[64];
  char Status[64];
  int syncO;
} auxscope_Metrology_cache;
