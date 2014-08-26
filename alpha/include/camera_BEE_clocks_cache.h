#define camera_BEE_clocks_revCode "9c9de87676ac699938d7a0e9b69e74f5"
typedef struct camera_BEE_clocks_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  long serial_1A[201];
  long serial_2A[201];
  long serial_3A[201];
  long serial_1B[201];
  long serial_2B[201];
  long serial_3B[201];
  long parallel_1A[201];
  long parallel_1B[201];
  long parallel_2A[201];
  long parallel_2B[201];
} camera_BEE_clocks_cache;
