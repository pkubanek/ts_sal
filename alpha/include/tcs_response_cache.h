#define tcs_response_revCode "819126f5d88fd71d89baa5b1a2718643"
typedef struct tcs_response_cache {
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
} tcs_response_cache;
