#define tcs_dome_revCode "0b01ee2b63546d97d464e4557f00399c"
typedef struct tcs_dome_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  char az[16];
  char error[16];
  char mode[16];
  char status[16];
} tcs_dome_cache;
