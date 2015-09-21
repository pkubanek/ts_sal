DROP TABLE IF EXISTS camera_UTIL_items;
CREATE TABLE camera_UTIL_items (
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
INSERT INTO camera_UTIL_items VALUES (1,"flow_rate","float",10,"",0.054,"","","");
INSERT INTO camera_UTIL_items VALUES (2,"temperature","float",10,"",0.054,"","","");
INSERT INTO camera_UTIL_items VALUES (3,"setpoint","float",10,"",0.054,"","","");
INSERT INTO camera_UTIL_items VALUES (4,"status"," unsignedlong",10,"",0.054,"","","");
