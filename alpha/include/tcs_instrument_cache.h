#define tcs_instrument_revCode "2f495e1ab55ef3f3dee9a121ee970d95"
typedef struct tcs_instrument_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  char name[16];
} tcs_instrument_cache;
