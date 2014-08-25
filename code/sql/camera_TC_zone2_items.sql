DROP TABLE IF EXISTS camera_TC_zone2_items;
CREATE TABLE camera_TC_zone2_items (
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
INSERT INTO camera_TC_zone2_items VALUES (1,"cold_plate","float",25,"",0.1,"","");
INSERT INTO camera_TC_zone2_items VALUES (2,"temperature","float",25,"",0.1,"","");
INSERT INTO camera_TC_zone2_items VALUES (3,"setpoint","float",25,"",0.1,"","");
INSERT INTO camera_TC_zone2_items VALUES (4,"status","long",25,"",0.1,"","");
