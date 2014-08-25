DROP TABLE IF EXISTS Cold_power_items;
CREATE TABLE Cold_power_items (
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
INSERT INTO Cold_power_items VALUES (1,"Compressor","float",1,"Watts",0.054,"","");
