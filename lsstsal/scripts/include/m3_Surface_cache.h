typedef struct m3_Surface_cache {
  int cppDummy;
  int syncI;
  long Raw[200];
  float Calibrated[200];
  long Status[50];
  int syncO;
} m3_Surface_cache;
