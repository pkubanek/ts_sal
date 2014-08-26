#define mse_adc1_revCode "bc1e6b81fe06b9acbc77d9fbab1091f2"
typedef struct mse_adc1_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  float angle;
  long zero;
} mse_adc1_cache;
