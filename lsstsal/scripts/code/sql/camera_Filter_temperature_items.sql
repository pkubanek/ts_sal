DROP TABLE IF EXISTS camera_Filter_temperature_items;
CREATE TABLE camera_Filter_temperature_items (
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
INSERT INTO camera_Filter_temperature_items VALUES (1,"Latch_temperature","float",10,"Celsius",2.31E-04,"none","Camera body","Carousel: 10 latch temperatures");
INSERT INTO camera_Filter_temperature_items VALUES (2,"Carousel_temperature","float",1,"Celsius",2.31E-04,"none","Camera body","Carousel: Motor temperature");
INSERT INTO camera_Filter_temperature_items VALUES (3,"Clamp_temperature","float",5,"Celsius",2.31E-04,"none","Camera body","Auto: Clamp temperatures");
INSERT INTO camera_Filter_temperature_items VALUES (4,"Auto_temperature","float",1,"Celsius",2.31E-04,"none","Camera body","Auto: Motor temperature");
