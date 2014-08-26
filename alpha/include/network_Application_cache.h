typedef struct network_Application_cache {
  int cppDummy;
  int syncI;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  long Data[64];
  char Status[16];
  int syncO;
} network_Application_cache;
