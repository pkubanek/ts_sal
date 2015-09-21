DROP TABLE IF EXISTS mount_TC_items;
CREATE TABLE mount_TC_items (
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
INSERT INTO mount_TC_items VALUES (1,"Raw","long",16,"",0.054,"","","");
INSERT INTO mount_TC_items VALUES (2,"Calibrated","float",16,"",0.054,"","","");
