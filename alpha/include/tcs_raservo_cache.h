#define tcs_raservo_revCode "57d1b8fdb4d6e19960c5e1d67278c711"
typedef struct tcs_raservo_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  float demand;
  float position;
  float error;
  float current;
  char state[16];
} tcs_raservo_cache;
