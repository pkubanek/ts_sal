DROP TABLE IF EXISTS camera_Cold_speed_items;
CREATE TABLE camera_Cold_speed_items (
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
INSERT INTO camera_Cold_speed_items VALUES (1,"Compressor_speed","float",6,"Hz",0.010,"none","Utility room","Compressor speed");
INSERT INTO camera_Cold_speed_items VALUES (2,"Dischaarge_pressure","float",6,"Pa",0.010,"none","Utility room","Compressor discharge  pressure");
INSERT INTO camera_Cold_speed_items VALUES (3,"Discharge_temp","float",6,"Celsius",0.010,"none","Utility room","Compressor discharge  temperature");
