DROP TABLE IF EXISTS Filter_speed_items;
CREATE TABLE Filter_speed_items (
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
INSERT INTO Filter_speed_items VALUES (1,"Carousel_speed","float",1,"m/s",0.054,"","");
INSERT INTO Filter_speed_items VALUES (2,"Truck_speed","float",1,"m/s",0.054,"","");
