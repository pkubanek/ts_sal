DROP TABLE IF EXISTS SAS_encoder_items;
CREATE TABLE SAS_encoder_items (
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
INSERT INTO SAS_encoder_items VALUES (1,"CABAC_MUX","long",12,"none",0.054,"","");
INSERT INTO SAS_encoder_items VALUES (2,"REB_ID"," unsignedshort",1,"",0.054,"","");
