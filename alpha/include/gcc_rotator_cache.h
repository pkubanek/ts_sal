#define gcc_rotator_revCode "fd2a9bca5db464ed050553a33afcc949"
typedef struct gcc_rotator_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  float angle;
  float resolution;
} gcc_rotator_cache;
