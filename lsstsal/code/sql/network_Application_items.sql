DROP TABLE IF EXISTS network_Application_items;
CREATE TABLE network_Application_items (
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
INSERT INTO network_Application_items VALUES (1,"Data","long",63,"",0.054,"","","");
