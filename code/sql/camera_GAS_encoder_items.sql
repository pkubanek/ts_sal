DROP TABLE IF EXISTS camera_GAS_encoder_items;
CREATE TABLE camera_GAS_encoder_items (
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
INSERT INTO camera_GAS_encoder_items VALUES (1,"CABAC_MUX","long",4,"none",0.054,"","","CABAC");
INSERT INTO camera_GAS_encoder_items VALUES (2,"REB_ID"," unsignedshort",1,"none",0.054,"none","Cryostat","Raft Electronics Board ID");
