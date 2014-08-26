typedef struct tcs_kernel_OpticsVt_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  float tip;
  float tilt;
} tcs_kernel_OpticsVt_cache;
