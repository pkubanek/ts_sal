DROP TABLE IF EXISTS camera_GDS_TCM_items;
CREATE TABLE camera_GDS_TCM_items (
  num	int,
  item	char(32),
  type  char(32),
  size  int,
  units char(32),
  freq  float,
  range char(32),
  location char(32),
  comment char(128),
  PRIMARY KEY (num)
);
INSERT INTO camera_GDS_TCM_items VALUES (1,"Timing_parameter","long",10,"none",0.054,"none","Science and corner rafts","Timing parameters[");
INSERT INTO camera_GDS_TCM_items VALUES (2,"REB_ID"," unsignedshort",1,"none",0.054,"none","Cryostat","Raft Electronics Board ID");
