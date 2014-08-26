typedef struct m3_Metrology_cache {
  int cppDummy;
  int syncI;
  long Raw[16];
  float Calibrated[16];
  long Limits[64];
  long Status[64];
  int syncO;
} m3_Metrology_cache;
