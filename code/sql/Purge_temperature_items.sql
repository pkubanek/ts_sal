DROP TABLE IF EXISTS Purge_temperature_items;
CREATE TABLE Purge_temperature_items (
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
INSERT INTO Purge_temperature_items VALUES (2,"Temp","float",1,"Celsius",0.054,"","");
INSERT INTO Purge_temperature_items VALUES (2,"Temp","float",1,"Celsius",0.054,"","");
