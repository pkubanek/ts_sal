typedef struct camera_QA_measured_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  float metric1[132];
  float metric2[132];
  float metric3[132];
  float metric4[132];
} camera_QA_measured_cache;
