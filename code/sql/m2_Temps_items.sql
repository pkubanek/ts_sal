DROP TABLE IF EXISTS m2_Temps_items;
CREATE TABLE m2_Temps_items (
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
INSERT INTO m2_Temps_items VALUES (1,"Raw_","long",15,"",0.054,"","","");
INSERT INTO m2_Temps_items VALUES (2,"Calibrated","float",15,"",0.054,"","","");
INSERT INTO m2_Temps_items VALUES (3,"Health","octet",15,"",0.054,"","","");
