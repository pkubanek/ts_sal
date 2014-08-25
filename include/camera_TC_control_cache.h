typedef struct camera_TC_control_cache {
  int cppDummy;
  int syncI;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  float temperature[10];
  float setpoint[10];
  long status[10];
  int syncO;
} camera_TC_control_cache;
