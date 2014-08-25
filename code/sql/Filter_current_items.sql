DROP TABLE IF EXISTS Filter_current_items;
CREATE TABLE Filter_current_items (
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
INSERT INTO Filter_current_items VALUES (1,"Carousel_current","float",1,"Amp",0.054,"","");
INSERT INTO Filter_current_items VALUES (2,"Auto_current","float",1,"Amp",0.054,"","");
