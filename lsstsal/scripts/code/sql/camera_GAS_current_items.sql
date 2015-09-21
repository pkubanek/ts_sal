DROP TABLE IF EXISTS camera_GAS_current_items;
CREATE TABLE camera_GAS_current_items (
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
INSERT INTO camera_GAS_current_items VALUES (1,"Board_current","float",4,"Volt",0.054,"","","Electronics board currents (4");
INSERT INTO camera_GAS_current_items VALUES (2,"REB_ID"," unsignedshort",1,"none",0.054,"none","Cryostat","Raft Electronics Board ID");
