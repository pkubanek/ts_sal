typedef struct camera_UTIL_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  float flow_rate[10];
  float temperature[10];
  float setpoint[10];
  long status[10];
} camera_UTIL_cache;
