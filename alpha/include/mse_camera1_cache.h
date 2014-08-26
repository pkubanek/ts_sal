#define mse_camera1_revCode "a89bc71d299a35d6d9e6f37f0a50ac2e"
typedef struct mse_camera1_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  float focus;
} mse_camera1_cache;
