typedef struct camera_WFS_cache {
  int cppDummy;
  int syncI;
  float Metadata[32];
  float Results[96];
  long Status[4];
  int syncO;
} camera_WFS_cache;
