#define icc_viewer_revCode "9af81473d7bc9755375cfacda4a158bb"
typedef struct icc_viewer_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  char position[16];
} icc_viewer_cache;
