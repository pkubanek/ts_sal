typedef struct camera_RAS_cache {
  int cppDummy;
  int syncI;
  long Raw[16];
  float Calibrated[16];
  long Limits[64];
  long Status[64];
  int syncO;
} camera_RAS_cache;
