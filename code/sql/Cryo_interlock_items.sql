DROP TABLE IF EXISTS Cryo_interlock_items;
CREATE TABLE Cryo_interlock_items (
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
INSERT INTO Cryo_interlock_items VALUES (1,"Flow_interlock","short",2,"none",0.054,"","");
