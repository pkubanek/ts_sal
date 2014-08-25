DROP TABLE IF EXISTS SAS_ID_items;
CREATE TABLE SAS_ID_items (
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
INSERT INTO SAS_ID_items VALUES (1,"CCD_ID","short",3,"none",0.054,"","");
INSERT INTO SAS_ID_items VALUES (2,"Board_ID","short",1,"none",0.054,"","");
INSERT INTO SAS_ID_items VALUES (3,"REB_ID"," unsignedshort",1,"",0.054,"","");
