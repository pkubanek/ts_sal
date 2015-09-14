typedef struct camera_GS_cache {
  int cppDummy;
  int syncI;
  float Profiles[8];
  float Fits[8];
  float Centroids[2];
  long Status[4];
  int syncO;
} camera_GS_cache;
