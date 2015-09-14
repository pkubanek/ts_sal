typedef struct m2_Hexapod_cache {
  int cppDummy;
  int syncI;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  long Raw[32];
  float Calibrated[32];
  char Status[32];
  int syncO;
} m2_Hexapod_cache;
