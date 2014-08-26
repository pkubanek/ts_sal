typedef struct environment_Video_cameras_cache {
  int cppDummy;
  int syncI;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  long Raw[16];
  float Calibrated[32];
  char Status[16];
  int syncO;
} environment_Video_cameras_cache;
