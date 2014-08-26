typedef struct system_Hardware_revision_history_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  char Component[32];
  char Reason[32];
  long Version[3];
} system_Hardware_revision_history_cache;
