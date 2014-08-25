DROP TABLE IF EXISTS Cryo_flow_items;
CREATE TABLE Cryo_flow_items (
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
INSERT INTO Cryo_flow_items VALUES (1,"Intake_flow","float",2,"lps",0.054,"","");
