#define icc_mirror_revCode "e21ceffa7b9e2b565f7ddda2c6fe7b34"
typedef struct icc_mirror_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  char position[16];
} icc_mirror_cache;
