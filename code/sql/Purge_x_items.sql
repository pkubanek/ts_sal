DROP TABLE IF EXISTS Purge_x_items;
CREATE TABLE Purge_x_items (
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
INSERT INTO Purge_x_items VALUES (1,"Valve_setting","long",1,"none",0.054,"","");
