DROP TABLE IF EXISTS m2_actuators_items;
CREATE TABLE m2_actuators_items (
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
INSERT INTO m2_actuators_items VALUES (1,"targetpos","long",72,"",0.054,"","","");
INSERT INTO m2_actuators_items VALUES (2,"stepcnt","long",72,"",0.054,"","","");
INSERT INTO m2_actuators_items VALUES (3,"force","float",72,"",0.054,"","","");
