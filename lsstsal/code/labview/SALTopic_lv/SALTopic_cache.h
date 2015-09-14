typedef struct SALTopic_cache {
  int cppDummy;
  int syncI;
  char 	     private_revCode[32];  //private
  double     private_sndStamp; //private
  double     private_rcvStamp; //private
  long       private_seqNum;   //private
  long       private_origin;   //private
  long       private_host;     //private
  short		test_i16;
  long		test_l32;
  long long	test_i64;
  unsigned short	test_u16;
  unsigned long	test_u32;
  unsigned long long	test_u64;
  float		test_r32;
  double	test_r64;
  char		test_u8;
  int		test_bool;
  short		test_i16_array[16];
  long		test_l32_array[16];
  long long	test_i64_array[16];
  unsigned short	test_u16_array[16];
  unsigned long	test_u32_array[16];
  unsigned long long	test_u64_array[16];
  float		test_r32_array[16];
  double	test_r64_array[16];
  char		test_u8_array[16];
  int		test_bool_array[16];
  char		test_string[32];
  char		test_string_option[16];
  char		test_large_string[4096];
  int syncO;
} SALTopic_cache;
