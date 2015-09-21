typedef struct camera_SDS_amplifiers_cache {
  int cppDummy;
  int syncI;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  short raftID;
  long flags[132];
  long status[132];
  float voltage1[132];
  float voltage2[132];
  float voltage3[132];
  float voltage4[132];
  int syncO;
} camera_SDS_amplifiers_cache;
