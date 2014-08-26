#define mse_main_revCode "ae5f1aecea41fe7dc0f1606bdc325fc4"
typedef struct mse_main_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  char host[16];
  char ident[16];
  char link[16];
  long pid;
} mse_main_cache;
