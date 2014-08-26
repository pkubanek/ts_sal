#define tcs_adc_revCode "673062ba466bc92bda32c00919a016c0"
typedef struct tcs_adc_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  float enc1;
  float enc2;
  float pos1;
  float pos2;
  char state[16];
} tcs_adc_cache;
