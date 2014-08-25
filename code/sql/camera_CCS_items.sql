DROP TABLE IF EXISTS camera_CCS_items;
CREATE TABLE camera_CCS_items (
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
INSERT INTO camera_CCS_items VALUES (1,"expHist"," unsignedlong",1024,"none",0.1,"","");
INSERT INTO camera_CCS_items VALUES (2,"flags"," unsignedlong",10,"none",0.1,"","");
