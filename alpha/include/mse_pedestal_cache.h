#define mse_pedestal_revCode "9a6ee423fdc1038b788fa42d5e6f98ed"
typedef struct mse_pedestal_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  long focus;
} mse_pedestal_cache;
