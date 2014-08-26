#define mse_adc2_revCode "829e1c9833bd31d7da7b7aed32109231"
typedef struct mse_adc2_cache {
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
} mse_adc2_cache;
