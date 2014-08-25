DROP TABLE IF EXISTS Cold_vacuum_items;
CREATE TABLE Cold_vacuum_items (
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
INSERT INTO Cold_vacuum_items VALUES (1,"Vacuum_gauge","float",5,"Pa",0.054,"","");
