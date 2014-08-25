DROP TABLE IF EXISTS Purge_acceleration_items;
CREATE TABLE Purge_acceleration_items (
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
INSERT INTO Purge_acceleration_items VALUES (1,"Accelerometer","float",6,"m/s2",0.054,"","");
