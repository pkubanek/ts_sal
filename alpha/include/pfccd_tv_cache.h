#define pfccd_tv_revCode "f7bd3d7e0ca5205fff26c92444d7cc16"
typedef struct pfccd_tv_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  long focus;
} pfccd_tv_cache;
