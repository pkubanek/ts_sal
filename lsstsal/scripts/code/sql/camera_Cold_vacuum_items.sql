DROP TABLE IF EXISTS camera_Cold_vacuum_items;
CREATE TABLE camera_Cold_vacuum_items (
  num	int,
  item	char(32),
  type  char(32),
  size  int,
  units char(32),
  freq  float,
  range char(32),
  location char(32),
  comment char(128),
  PRIMARY KEY (num)
);
INSERT INTO camera_Cold_vacuum_items VALUES (1,"Vacuum_gauge","float",5,"Pa",0.010,"none","Utility trunk","3 for cryostat, 2 for heat exchangers");
