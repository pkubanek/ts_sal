#define tcs_calibration_revCode "768f90a333033304c5eca17c3ff4e95e"
typedef struct tcs_calibration_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  long lamp[8];
  char state[16];
} tcs_calibration_cache;
