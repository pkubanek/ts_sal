DROP TABLE IF EXISTS hexapod_Metrology_items;
CREATE TABLE hexapod_Metrology_items (
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
INSERT INTO hexapod_Metrology_items VALUES (1,"distance","long",18,"",0.054,"","","");
INSERT INTO hexapod_Metrology_items VALUES (2,"error","long",18,"",0.054,"","","");
INSERT INTO hexapod_Metrology_items VALUES (3,"status","short",18,"",0.054,"","","");
