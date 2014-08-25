DROP TABLE IF EXISTS camera_TC_zone1_items;
CREATE TABLE camera_TC_zone1_items (
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
INSERT INTO camera_TC_zone1_items VALUES (1,"cold_plate","float",25,"",0.1,"","");
INSERT INTO camera_TC_zone1_items VALUES (2,"flow_rate","float",25,"",0.1,"","");
INSERT INTO camera_TC_zone1_items VALUES (3,"temperature","float",25,"",0.1,"","");
INSERT INTO camera_TC_zone1_items VALUES (4,"setpoint","float",25,"",0.1,"","");
INSERT INTO camera_TC_zone1_items VALUES (5,"status","long",25,"",0.1,"","");
