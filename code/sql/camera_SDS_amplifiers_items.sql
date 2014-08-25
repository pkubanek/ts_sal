DROP TABLE IF EXISTS camera_SDS_amplifiers_items;
CREATE TABLE camera_SDS_amplifiers_items (
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
INSERT INTO camera_SDS_amplifiers_items VALUES (1,"raftID"," unsignedshort",1,"none",0.1,"","");
INSERT INTO camera_SDS_amplifiers_items VALUES (2,"flags"," unsignedlong",132,"none",0.1,"","");
INSERT INTO camera_SDS_amplifiers_items VALUES (3,"status"," unsignedlong",132,"none",0.1,"","");
INSERT INTO camera_SDS_amplifiers_items VALUES (4,"voltage1","float",132,"none",0.1,"","");
INSERT INTO camera_SDS_amplifiers_items VALUES (5,"voltage2","float",132,"none",0.1,"","");
INSERT INTO camera_SDS_amplifiers_items VALUES (6,"voltage3","float",132,"none",0.1,"","");
INSERT INTO camera_SDS_amplifiers_items VALUES (7,"voltage4","float",132,"none",0.1,"","");
