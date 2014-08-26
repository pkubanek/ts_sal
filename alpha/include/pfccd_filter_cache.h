#define pfccd_filter_revCode "8d33b19a5fd75746d6acb6103e8ee4ae"
typedef struct pfccd_filter_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  char current[16];
  char name1[16];
  char name2[16];
  char name3[16];
  char name4[16];
  char name5[16];
  char name6[16];
  char name7[16];
  char name8[16];
  long position;
} pfccd_filter_cache;
