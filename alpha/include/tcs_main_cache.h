#define tcs_main_revCode "437cac73ce8fb40d2f130ae7dda232ee"
typedef struct tcs_main_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  char computer[16];
  char host[16];
  char link[16];
  long pid;
  char updates[16];
} tcs_main_cache;
