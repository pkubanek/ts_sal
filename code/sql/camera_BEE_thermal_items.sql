DROP TABLE IF EXISTS camera_BEE_thermal_items;
CREATE TABLE camera_BEE_thermal_items (
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
INSERT INTO camera_BEE_thermal_items VALUES (1,"raftID"," unsignedshort",1,"none",0.1,"","");
INSERT INTO camera_BEE_thermal_items VALUES (2,"temp","float",20,"0.0,200.0",0.1,"","");
INSERT INTO camera_BEE_thermal_items VALUES (3,"heaterPower","float",10,"0.0,10.0",0.1,"","");
INSERT INTO camera_BEE_thermal_items VALUES (4,"heaterStatus","long",10,"none",0.1,"","");
INSERT INTO camera_BEE_thermal_items VALUES (5,"cfgChkSum"," unsignedlong",1,"none",0.1,"","");
