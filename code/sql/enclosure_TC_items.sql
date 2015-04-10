DROP TABLE IF EXISTS enclosure_TC_items;
CREATE TABLE enclosure_TC_items (
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
INSERT INTO enclosure_TC_items VALUES (1,"raw","long",16,"",0.054,"","","");
INSERT INTO enclosure_TC_items VALUES (2,"calibrated","float",16,"",0.054,"","","");
INSERT INTO enclosure_TC_items VALUES (3,"setPoint","float",16,"",0.054,"","","");
INSERT INTO enclosure_TC_items VALUES (4,"status","long",16,"",0.054,"","","");
INSERT INTO enclosure_TC_items VALUES (5,"glycolFlow","float",4,"",0.054,"","","");
INSERT INTO enclosure_TC_items VALUES (6,"glycolTemperature","float",4,"",0.054,"","","");
INSERT INTO enclosure_TC_items VALUES (7,"boosterSpeed","float",4,"",0.054,"","","");
