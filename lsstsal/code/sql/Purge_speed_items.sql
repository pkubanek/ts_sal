DROP TABLE IF EXISTS Purge_speed_items;
CREATE TABLE Purge_speed_items (
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
INSERT INTO Purge_speed_items VALUES (1,"Blower_setting","float",1,"Hz",0.054,"","");
INSERT INTO Purge_speed_items VALUES (2,"Blower_speed","float",1,"Hz",0.054,"","");
