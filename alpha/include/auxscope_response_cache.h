typedef struct auxscope_response_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  long cmdID;
  char ack[16];
  char error[16];
  long timeout;
  short repeat;
  short submits;
  char result[64];
} auxscope_response_cache;
