typedef struct camera_TC_cache {
  int cppDummy;
  int syncI;
  long HeaterRaw[16];
  float HeaterCalibrated[32];
  long HeaterStatus[4];
  int syncO;
} camera_TC_cache;
