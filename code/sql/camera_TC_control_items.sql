DROP TABLE IF EXISTS camera_TC_control_items;
CREATE TABLE camera_TC_control_items (
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
INSERT INTO camera_TC_control_items VALUES (1,"temperature","float",10,"none",0.1,"","");
INSERT INTO camera_TC_control_items VALUES (2,"setpoint","float",10,"none",0.1,"","");
INSERT INTO camera_TC_control_items VALUES (3,"status"," unsignedlong",10,"none",0.1,"","");
