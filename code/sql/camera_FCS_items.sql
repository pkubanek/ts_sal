DROP TABLE IF EXISTS camera_FCS_items;
CREATE TABLE camera_FCS_items (
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
INSERT INTO camera_FCS_items VALUES (1,"motion_profile","float",2400,"none",0.1,"","");
INSERT INTO camera_FCS_items VALUES (2,"algorithm","string",32,"none",0.1,"","");
INSERT INTO camera_FCS_items VALUES (3,"flags"," unsignedlong",1,"none",0.1,"","");
