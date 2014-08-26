#define pfccd_scantable_revCode "0b5ce59df17ba15331f7a14337cd306d"
typedef struct pfccd_scantable_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  long position;
  long stepsize;
} pfccd_scantable_cache;
