typedef struct m1m3_Application_cache {
  int cppDummy;
  int syncI;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  float Demand[32];
  float Position[32];
  float Error[32];
  char Status[32];
  int syncO;
} m1m3_Application_cache;
