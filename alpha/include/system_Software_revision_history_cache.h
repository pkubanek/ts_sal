typedef struct system_Software_revision_history_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  char Module[32];
  char Notes[32];
  long Version[3];
} system_Software_revision_history_cache;
