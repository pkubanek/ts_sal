typedef struct seeing_dimm_Application_cache {
  int cppDummy;
  int syncI;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  long Raw[16];
  float Calibrated[32];
  float Error[4];
  char Status[16];
  int syncO;
} seeing_dimm_Application_cache;
