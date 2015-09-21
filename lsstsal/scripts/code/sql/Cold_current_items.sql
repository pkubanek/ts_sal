DROP TABLE IF EXISTS Cold_current_items;
CREATE TABLE Cold_current_items (
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
INSERT INTO Cold_current_items VALUES (1,"Ion_pump","float",4,"Amp",0.054,"","");
INSERT INTO Cold_current_items VALUES (2,"Heater_current","float",6,"Amp",0.054,"","");
