#define tcs_command_revCode "9540443c5693d7ae5af8d110c2abde27"
typedef struct tcs_command_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  long cmdID;
  char device[16];
  char operation[16];
  char value[16];
  char modifiers[128];
} tcs_command_cache;
