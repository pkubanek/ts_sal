#define system_Command_history_revCode "3c685ba3ab0714f9a84c50a50e1996e0"
typedef struct system_Command_history_cache {
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
  char ack[16];
  char error[16];
  long clkdrift;
  long timeout;
  short repeat;
  short submits;
  char result[64];
} system_Command_history_cache;
