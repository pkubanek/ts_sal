DROP TABLE IF EXISTS power_Electrical_items;
CREATE TABLE power_Electrical_items (
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
INSERT INTO power_Electrical_items VALUES (1,"Raw","long",16,"",1,"","","");
INSERT INTO power_Electrical_items VALUES (2,"Calibrated","float",32,"",1,"","","");
