typedef struct m1m3_command_cache {
  int cppDummy;
  int syncI;
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
  int syncO;
} m1m3_command_cache;
