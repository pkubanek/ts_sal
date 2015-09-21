DROP TABLE IF EXISTS Filter_position_items;
CREATE TABLE Filter_position_items (
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
INSERT INTO Filter_position_items VALUES (1,"Carousel_position","float",1,"Radian",0.054,"","");
INSERT INTO Filter_position_items VALUES (2,"Truck_position","float",1,"m",0.054,"","");
INSERT INTO Filter_position_items VALUES (3,"Rail_position","float",2,"m",0.054,"","");
