#define mse_shutter_revCode "e533741dcd160ebbc7605dd9741a7b6f"
typedef struct mse_shutter_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  char position[16];
  char ready[16];
} mse_shutter_cache;
