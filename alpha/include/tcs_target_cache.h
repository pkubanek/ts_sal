#define tcs_target_revCode "27edc97f65d7a8f8bcc7b6746a92cf1e"
typedef struct tcs_target_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  char dec[16];
  char dec_preset[16];
  char epoch[16];
  char epoch_preset[16];
  char ra[16];
  char ra_preset[16];
} tcs_target_cache;
