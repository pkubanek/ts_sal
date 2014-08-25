typedef struct m1_Actuators_cache {
  int cppDummy;
  int syncI;
  long Raw[16];
  float Calibrated[32];
  long Status[4];
  int syncO;
} m1_Actuators_cache;
