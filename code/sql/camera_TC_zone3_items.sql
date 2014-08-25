DROP TABLE IF EXISTS camera_TC_zone3_items;
CREATE TABLE camera_TC_zone3_items (
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
INSERT INTO camera_TC_zone3_items VALUES (1,"temperature","float",50,"",0.054,"","","");
INSERT INTO camera_TC_zone3_items VALUES (2,"setpoint","float",50,"",0.054,"","","");
INSERT INTO camera_TC_zone3_items VALUES (3,"status"," unsignedlong",50,"",0.054,"","","");
