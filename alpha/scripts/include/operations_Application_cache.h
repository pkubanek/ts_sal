typedef struct operations_Application_cache {
  int cppDummy;
  int syncI;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  char Status[50];
  float data[200];
  int syncO;
} operations_Application_cache;
