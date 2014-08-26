#define tcs_guider_revCode "eb49b858dd0251107e939858908a0fc6"
typedef struct tcs_guider_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  char calibration[16];
  char leaky[16];
  char mode[16];
  char motion[16];
  char northx[16];
  char northy[16];
  char probe[16];
  char southx[16];
  char southy[16];
  char update[16];
} tcs_guider_cache;
