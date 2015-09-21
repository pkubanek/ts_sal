DROP TABLE IF EXISTS camera_Filter_position_items;
CREATE TABLE camera_Filter_position_items (
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
INSERT INTO camera_Filter_position_items VALUES (1,"Carousel_position","float",1,"Radian",2.31E-04,"none","Camera body","Carousel:Position");
INSERT INTO camera_Filter_position_items VALUES (2,"Truck_position","float",1,"m",2.31E-04,"none","Camera body","Auto: Truck position");
INSERT INTO camera_Filter_position_items VALUES (3,"Rail_position","float",2,"m",2.31E-04,"none","Camera body","Auto: Rail position");
