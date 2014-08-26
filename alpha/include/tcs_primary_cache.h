#define tcs_primary_revCode "74b111a730d1e3e418629aeb5b0ce290"
typedef struct tcs_primary_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  double fp[3];
  float sinner;
  float souter;
  double tinner[13];
  double touter[20];
  double inner[13];
  double outer[20];
  long flags;
  char mcover[16];
} tcs_primary_cache;
