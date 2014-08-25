typedef struct camera_PWR_cache {
  int cppDummy;
  int syncI;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  float supply_voltage[25];
  float current[25];
  int syncO;
} camera_PWR_cache;
