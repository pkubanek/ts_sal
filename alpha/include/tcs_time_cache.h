#define tcs_time_revCode "77d350067889a41456a661a25e1a4f74"
typedef struct tcs_time_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  char st[16];
  char ut[16];
  char utdate[16];
} tcs_time_cache;
