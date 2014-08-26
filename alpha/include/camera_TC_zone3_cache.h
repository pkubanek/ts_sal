typedef struct camera_TC_zone3_cache {
  int cppDummy;
  int syncI;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  float temperature[50];
  float setpoint[50];
  long status[50];
  int syncO;
} camera_TC_zone3_cache;
