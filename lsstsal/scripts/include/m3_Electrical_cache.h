typedef struct m3_Electrical_cache {
  int cppDummy;
  int syncI;
  long Raw[16];
  float Calibrated[32];
  long Status[4];
  int syncO;
} m3_Electrical_cache;
