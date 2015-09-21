typedef struct tcs_kernel_DawdleFilter_cache {
  int cppDummy;
  int syncI;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  long Bypass;
  float T;
  int syncO;
} tcs_kernel_DawdleFilter_cache;
