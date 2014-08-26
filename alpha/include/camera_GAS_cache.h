typedef struct camera_GAS_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  char algorithm[32];
  float parameters[10];
  float sampleData_00[25];
  float sampleData_01[25];
  float sampleData_10[25];
  float sampleData_11[25];
} camera_GAS_cache;
