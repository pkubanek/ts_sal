DROP TABLE IF EXISTS  camera_Shutter_time_items;
CREATE TABLE  camera_Shutter_time_items (
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
INSERT INTO  camera_Shutter_time_items VALUES (1,"Close_profile","float",24,"seconds",0.054,"","");
