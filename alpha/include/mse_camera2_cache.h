#define mse_camera2_revCode "adb4f10857aa559176b9af9236ada12e"
typedef struct mse_camera2_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  float focus;
} mse_camera2_cache;
