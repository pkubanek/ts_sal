#define mse_filter_revCode "5ffcc95172c5114940898d51576fcad7"
typedef struct mse_filter_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  long position;
} mse_filter_cache;
