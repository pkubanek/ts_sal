typedef struct camera_SCU_cache {
  int cppDummy;
  int syncI;
  long Raw[1024];
  float Position[32];
  long Status[4];
  int syncO;
} camera_SCU_cache;
