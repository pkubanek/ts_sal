typedef struct camera_TC_zone2_cache {
  int cppDummy;
  int syncI;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  float cold_plate[25];
  float temperature[25];
  float setpoint[25];
  long status[25];
  int syncO;
} camera_TC_zone2_cache;
