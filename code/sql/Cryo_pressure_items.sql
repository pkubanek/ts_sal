DROP TABLE IF EXISTS Cryo_pressure_items;
CREATE TABLE Cryo_pressure_items (
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
INSERT INTO Cryo_pressure_items VALUES (1,"Intake_pressure","float",2,"Pa",0.054,"","");
INSERT INTO Cryo_pressure_items VALUES (2,"Pre_expansion_pressure","float",2,"Pa",0.054,"","");
INSERT INTO Cryo_pressure_items VALUES (3,"Post_expansion_pressure","float",2,"Pa",0.054,"","");
