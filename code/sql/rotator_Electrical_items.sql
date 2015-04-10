DROP TABLE IF EXISTS rotator_Electrical_items;
CREATE TABLE rotator_Electrical_items (
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
INSERT INTO rotator_Electrical_items VALUES (1,"voltage","long",16,"",0.054,"","","");
INSERT INTO rotator_Electrical_items VALUES (2,"error","long",16,"",0.054,"","","");
INSERT INTO rotator_Electrical_items VALUES (3,"status","short",16,"",0.054,"","","");
