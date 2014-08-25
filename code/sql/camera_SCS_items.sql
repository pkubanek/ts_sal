DROP TABLE IF EXISTS camera_SCS_items;
CREATE TABLE camera_SCS_items (
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
INSERT INTO camera_SCS_items VALUES (1,"open_profile","float",1024,"none",0.1,"","");
INSERT INTO camera_SCS_items VALUES (2,"close_profile","float",1024,"none",0.1,"","");
INSERT INTO camera_SCS_items VALUES (3,"algorithm","string",32,"none",0.1,"","");
INSERT INTO camera_SCS_items VALUES (4,"flags"," unsignedlong",1,"none",0.1,"","");
