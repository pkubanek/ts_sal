typedef struct tcs_kernel_TimeKeeper_cache {
  int cppDummy;
  int syncI;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  float Tai;
  float Tt;
  float Cst;
  float Sst;
  float Dcst;
  float Dsst;
  int syncO;
} tcs_kernel_TimeKeeper_cache;
