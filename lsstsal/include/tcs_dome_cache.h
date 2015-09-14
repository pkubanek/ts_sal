typedef struct tcs_dome_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  float pos;
  char state[16];
  char alarm[16];
  char shutter[16];
} tcs_dome_cache;
