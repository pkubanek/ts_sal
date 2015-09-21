typedef struct camera_TC_zone6_cache {
  int cppDummy;
  int syncI;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  float flow_rate[10];
  float temperature[10];
  float setpoint[10];
  long status[10];
  int syncO;
} camera_TC_zone6_cache;
