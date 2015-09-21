DROP TABLE IF EXISTS camera_Filter_speed_items;
CREATE TABLE camera_Filter_speed_items (
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
INSERT INTO camera_Filter_speed_items VALUES (1,"Carousel_speed","float",1,"m",2.31E-04,"","","");
INSERT INTO camera_Filter_speed_items VALUES (2,"Truck_speed","float",1,"m",2.31E-04,"","","");
