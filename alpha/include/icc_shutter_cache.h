#define icc_shutter_revCode "6cebf65cf59e3558aed39d1f7ec20e16"
typedef struct icc_shutter_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  char position[16];
} icc_shutter_cache;
