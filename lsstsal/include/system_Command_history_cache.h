typedef struct system_Command_history_cache {
  int cppDummy;
  int syncI;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  char Command[32];
  float Data[16];
  char Status[16];
  int syncO;
} system_Command_history_cache;
