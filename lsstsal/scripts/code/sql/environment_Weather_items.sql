DROP TABLE IF EXISTS environment_Weather_items;
CREATE TABLE environment_Weather_items (
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
INSERT INTO environment_Weather_items VALUES (1,"Raw","long",128,"",1,"","","");
INSERT INTO environment_Weather_items VALUES (2,"Calibrated","float",256,"",1,"","","");
