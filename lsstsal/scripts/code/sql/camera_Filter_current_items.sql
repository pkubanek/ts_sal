DROP TABLE IF EXISTS camera_Filter_current_items;
CREATE TABLE camera_Filter_current_items (
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
INSERT INTO camera_Filter_current_items VALUES (1,"Carousel_current","float",1,"Amp",2.31E-04,"none","Camera body","Carousel: motor current");
INSERT INTO camera_Filter_current_items VALUES (2,"Auto_current","float",1,"Amp",2.31E-04,"none","Camera body","Auto: Motor current");
