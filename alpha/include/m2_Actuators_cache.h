typedef struct m2_Actuators_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  long Raw[16];
  float Calibrated[32];
} m2_Actuators_cache;
