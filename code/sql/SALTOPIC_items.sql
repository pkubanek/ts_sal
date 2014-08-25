DROP TABLE IF EXISTS SALTOPIC_items;
CREATE TABLE SALTOPIC_items (
  num	int,
  item	char(32),
  type  char(32),
  size  int,
  units char(32),
  freq  float,
  range char(32),
  comment char(128),
  PRIMARY KEY (num)
);
INSERT INTO SALTOPIC_items VALUES (1,"test_i16","short",1,"microns",0.1,"-1000,1000","Test signed short");
INSERT INTO SALTOPIC_items VALUES (2,"test_l32","long",1,"microns",0.1,"-1000,1000","Test signed 32 bit int");
INSERT INTO SALTOPIC_items VALUES (3,"test_i64","longlong",1,"microns",0.1,"-1000,1000","Test signed 64 bit int");
INSERT INTO SALTOPIC_items VALUES (4,"test_u16"," unsignedshort",1,"microns",0.1,"-1000,1000","Test unsigned short");
INSERT INTO SALTOPIC_items VALUES (5,"test_u32"," unsignedlong",1,"microns",0.1,"-1000,1000","Test unsigned 32 bit int");
INSERT INTO SALTOPIC_items VALUES (6,"test_u64"," unsignedlonglong",1,"microns",0.1,"-1000,1000","Test unsigned 64 bit int");
INSERT INTO SALTOPIC_items VALUES (7,"test_r32","float",1,"microns",0.1,"-1000.,1000.","Test floating point");
INSERT INTO SALTOPIC_items VALUES (8,"test_r64","double",1,"microns",0.1,"-1000.,1000.","Test double");
INSERT INTO SALTOPIC_items VALUES (9,"test_u8","char",1,"none",0.1,"none","Test char");
INSERT INTO SALTOPIC_items VALUES (10,"test_bool","boolean",1,"none",0.1,"none","Test booean");
INSERT INTO SALTOPIC_items VALUES (11,"test_i16_array","short",16,"microns",0.1,"-1000,1000","Test signed short array");
INSERT INTO SALTOPIC_items VALUES (12,"test_l32_array","long",16,"microns",0.1,"-1000,1000","Test signed 32 bit int array");
INSERT INTO SALTOPIC_items VALUES (13,"test_i64_array","longlong",16,"microns",0.1,"-1000,1000","Test signed 64 bit int array");
INSERT INTO SALTOPIC_items VALUES (14,"test_u16_array"," unsignedshort",16,"microns",0.1,"-1000,1000","Test unsigned short array");
INSERT INTO SALTOPIC_items VALUES (15,"test_u32_array"," unsignedlong",16,"microns",0.1,"-1000,1000","Test unsigned 32 bit int array");
INSERT INTO SALTOPIC_items VALUES (16,"test_u64_array"," unsignedlonglong",16,"microns",0.1,"-1000,1000","Test unsigned 64 bit int array");
INSERT INTO SALTOPIC_items VALUES (17,"test_r32_array","float",16,"microns",0.1,"-1000.,1000.","Test float array");
INSERT INTO SALTOPIC_items VALUES (18,"test_r64_array","double",16,"microns",0.1,"-1000.,1000.","Test double array");
INSERT INTO SALTOPIC_items VALUES (19,"test_u8_array","char",16,"none",0.1,"none","Test char array");
INSERT INTO SALTOPIC_items VALUES (20,"test_bool_array","boolean",16,"none",0.1,"none","Test booean array");
INSERT INTO SALTOPIC_items VALUES (21,"test_string","string",32,"none",0.1,"none","Test string");
INSERT INTO SALTOPIC_items VALUES (22,"test_string_option","string",16,"none",0.1,"yes,no,maybe","Test string option");
INSERT INTO SALTOPIC_items VALUES (23,"test_large_string","string",4096,"none",0.1,"none","Test large string");
