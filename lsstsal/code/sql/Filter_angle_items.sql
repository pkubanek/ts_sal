DROP TABLE IF EXISTS Filter_angle_items;
CREATE TABLE Filter_angle_items (
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
INSERT INTO Filter_angle_items VALUES (1,"Inclinometer","float",2,"Degrees",0.054,"","");
