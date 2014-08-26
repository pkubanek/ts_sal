#define pmtc_pmcch_revCode "98f4554d0c245871b6586e65b7fceb6d"
typedef struct pmtc_pmcch_cache {
  int cppDummy;
  int syncI;
  int syncO;
  char private_revCode[32];
  long private_sndStamp;
  long private_rcvStamp;
  long private_seqNum;
  long private_origin;
  char cch_start[16];
  char cch_stop[16];
  char flow_alarm[16];
  long flow_rate;
  long mode;
  char pump[16];
  long set_point;
  long status;
} pmtc_pmcch_cache;
