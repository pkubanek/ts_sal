DROP TABLE IF EXISTS Cryo_temperature_items;
CREATE TABLE Cryo_temperature_items (
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
INSERT INTO Cryo_temperature_items VALUES (1,"Cold_temperature","float",3,"Kelvin",0.054,"","");
INSERT INTO Cryo_temperature_items VALUES (2,"Cryo_temperature","float",12,"Kelvin",0.054,"","");
INSERT INTO Cryo_temperature_items VALUES (3,"Intake_temp","float",2,"Celsius",0.054,"","");
INSERT INTO Cryo_temperature_items VALUES (4,"Pre_expansion_temp","float",2,"Celsius",0.054,"","");
INSERT INTO Cryo_temperature_items VALUES (5,"Post_expansion_temp","float",2,"Celsius",0.054,"","");
INSERT INTO Cryo_temperature_items VALUES (6,"Return_temp","float",2,"Celsius",0.054,"","");
