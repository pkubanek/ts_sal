#define pmtc_main_revCode "65690d7f8214e2a1f1401a24395ed636"
typedef struct pmtc_main_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  float amt;
  char cooling[16];
  float dew_point;
  float dmt;
  float humidity;
  char link[16];
  float probe_temp;
  char simulation[16];
} pmtc_main_cache;
