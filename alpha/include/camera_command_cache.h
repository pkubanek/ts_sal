#define camera_command_revCode "655fcd30706b1046bef0d6c4208567fb"
typedef struct camera_command_cache {
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
} camera_command_cache;
