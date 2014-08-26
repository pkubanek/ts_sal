#define icc_lens_revCode "cc312f155b7826278fbd91b3a4bf4c93"
typedef struct icc_lens_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  char position[16];
} icc_lens_cache;
