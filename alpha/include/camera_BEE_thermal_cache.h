#define camera_BEE_thermal_revCode "0a8720e90fd3db2f8825cb78b9bd4702"
typedef struct camera_BEE_thermal_cache {
  int cppDummy;
  int syncI;
  int syncO;
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
} camera_BEE_thermal_cache;
