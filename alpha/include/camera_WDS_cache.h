typedef struct camera_WDS_cache {
  int cppDummy;
  int syncI;
  float Metadata[32];
  float results[96];
  long Status[4];
  int syncO;
} camera_WDS_cache;
