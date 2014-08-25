DROP TABLE IF EXISTS Cold_temperature_items;
CREATE TABLE Cold_temperature_items (
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
INSERT INTO Cold_temperature_items VALUES (1,"UtilityRoom_temperature","float",1,"Celsius",0.054,"","");
INSERT INTO Cold_temperature_items VALUES (2,"Intake_temp","float",6,"Celsius",0.054,"","");
INSERT INTO Cold_temperature_items VALUES (3,"Pre_expansion_temp","float",6,"Celsius",0.054,"","");
INSERT INTO Cold_temperature_items VALUES (4,"Post_expansion_temp","float",6,"Celsius",0.054,"","");
INSERT INTO Cold_temperature_items VALUES (5,"Return_temp","float",6,"Celsius",0.054,"","");
