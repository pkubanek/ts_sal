DROP TABLE IF EXISTS camera_WAS_ID_items;
CREATE TABLE camera_WAS_ID_items (
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
INSERT INTO camera_WAS_ID_items VALUES (1,"CCD_ID","short",1,"none",2.31E-05,"none","Corner rafts","CCD ID ( ITL only)");
INSERT INTO camera_WAS_ID_items VALUES (2,"Board_ID","short",1,"none",2.31E-05,"none","Corner rafts","Board ID");
INSERT INTO camera_WAS_ID_items VALUES (3,"REB_ID"," unsignedshort",1,"none",0.054,"none","Cryostat","Raft Electronics Board ID");
