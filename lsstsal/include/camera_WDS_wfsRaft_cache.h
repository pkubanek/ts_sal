typedef struct camera_WDS_wfsRaft_cache {
  int cppDummy;
  int syncI;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  float parameters[32];
  float metrics[32];
  float zernikes[16];
  long status;
  char avgInsideImage[128];
  char avgOutsideImage[128];
  char CalcImage1[128];
  char CalcImage2[128];
  int syncO;
} camera_WDS_wfsRaft_cache;
