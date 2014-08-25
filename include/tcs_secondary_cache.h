typedef struct tcs_secondary_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  float enctip;
  float enctilt;
  float tip;
  float tilt;
  float pressure;
  char state[16];
  char mcover[16];
} tcs_secondary_cache;
