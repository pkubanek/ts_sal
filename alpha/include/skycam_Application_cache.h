typedef struct skycam_Application_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  float Sky_parms[32];
  char Catalog[4096];
  float Data[64];
  float Error[4];
  char Status[16];
} skycam_Application_cache;
