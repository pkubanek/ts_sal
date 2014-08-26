typedef struct tcs_kernel_PointingControl_cache {
  int cppDummy;
  int syncI;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  char RollFilter[32];
  char PitchFilter[32];
  float AGuide;
  float BGuide;
  float ALocal;
  float BLocal;
  int syncO;
} tcs_kernel_PointingControl_cache;
