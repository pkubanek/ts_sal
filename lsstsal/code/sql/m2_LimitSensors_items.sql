DROP TABLE IF EXISTS m2_LimitSensors_items;
CREATE TABLE m2_LimitSensors_items (
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
INSERT INTO m2_LimitSensors_items VALUES (1,"liftoff","short",64,"",0.054,"","","");
INSERT INTO m2_LimitSensors_items VALUES (2,"limit","short",64,"",0.054,"","","");
