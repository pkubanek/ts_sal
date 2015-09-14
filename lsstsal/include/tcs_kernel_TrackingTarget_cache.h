typedef struct tcs_kernel_TrackingTarget_cache {
  int cppDummy;
  int syncI;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  float PositionX;
  float PositionY;
  float T0;
  float VelocityX;
  float VelocityY;
  int syncO;
} tcs_kernel_TrackingTarget_cache;
