typedef struct camera_SAS_cache {
  int cppDummy;
  int syncI;
  long Raw[16];
  float Calibrated[32];
  long Status[4];
  int syncO;
} camera_SAS_cache;
