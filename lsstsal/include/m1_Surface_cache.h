typedef struct m1_Surface_cache {
  int cppDummy;
  int syncI;
  long Raw[1024];
  float Calibrated[1024];
  long Status[256];
  int syncO;
} m1_Surface_cache;
