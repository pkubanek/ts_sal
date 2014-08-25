DROP TABLE IF EXISTS camera_WAS_temperature_items;
CREATE TABLE camera_WAS_temperature_items (
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
INSERT INTO camera_WAS_temperature_items VALUES (1,"CCD_temp","float",1,"Kelvin",0.054,"none","Corner rafts","CCD temperatures");
INSERT INTO camera_WAS_temperature_items VALUES (2,"Board_temp","float",12,"Kelvin",0.054,"none","Corner rafts","Board temps");
INSERT INTO camera_WAS_temperature_items VALUES (3,"REB_ID"," unsignedshort",1,"none",0.054,"none","Cryostat","Raft Electronics Board ID");
