typedef struct camera_BEE_thermal_cache {
  int cppDummy;
  int syncI;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  short raftID;
  float temp[20];
  float heaterPower[10];
  long heaterStatus[10];
  long cfgChkSum;
  int syncO;
} camera_BEE_thermal_cache;
