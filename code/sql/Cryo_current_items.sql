DROP TABLE IF EXISTS Cryo_current_items;
CREATE TABLE Cryo_current_items (
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
INSERT INTO Cryo_current_items VALUES (1,"Heater_current","float",6,"Amp",0.054,"","");
