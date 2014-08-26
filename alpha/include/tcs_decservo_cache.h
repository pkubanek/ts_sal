#define tcs_decservo_revCode "8fb83274bb2f50885c73e50419d8dbc1"
typedef struct tcs_decservo_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  float demand;
  float position;
  float error;
  float current;
  char state[16];
} tcs_decservo_cache;
