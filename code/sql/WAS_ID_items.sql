DROP TABLE IF EXISTS WAS_ID_items;
CREATE TABLE WAS_ID_items (
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
INSERT INTO WAS_ID_items VALUES (1,"CCD_ID","short",1,"none",0.054,"","");
INSERT INTO WAS_ID_items VALUES (2,"Board_ID","short",1,"none",0.054,"","");
INSERT INTO WAS_ID_items VALUES (3,"REB_ID"," unsignedshort",1,"",0.054,"","");
