DROP TABLE IF EXISTS dome_Metrology_items;
CREATE TABLE dome_Metrology_items (
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
INSERT INTO dome_Metrology_items VALUES (1,"azEncoder","long",4,"",0.054,"","","");
INSERT INTO dome_Metrology_items VALUES (2,"azCalibrated","float",4,"",0.054,"","","");
INSERT INTO dome_Metrology_items VALUES (3,"elevEncoder","long",4,"",0.054,"","","");
INSERT INTO dome_Metrology_items VALUES (4,"elevCalibrated","float",4,"",0.054,"","","");
INSERT INTO dome_Metrology_items VALUES (5,"screenEncoder","long",4,"",0.054,"","","");
INSERT INTO dome_Metrology_items VALUES (6,"shutterL","long",4,"",0.054,"","","");
INSERT INTO dome_Metrology_items VALUES (7,"shutterR","long",4,"",0.054,"","","");
