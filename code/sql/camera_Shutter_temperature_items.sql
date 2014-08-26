DROP TABLE IF EXISTS camera_Shutter_temperature_items;
CREATE TABLE camera_Shutter_temperature_items (
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
INSERT INTO camera_Shutter_temperature_items VALUES (1,"Motor_temp","float",2,"none",0.054,"none","Camera body","Shutter motor temperatures");