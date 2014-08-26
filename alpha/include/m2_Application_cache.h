typedef struct m2_Application_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  float Demand[4];
  float Position[4];
  float Error[4];
  char Status[16];
} m2_Application_cache;
