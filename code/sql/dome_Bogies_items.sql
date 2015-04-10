DROP TABLE IF EXISTS dome_Bogies_items;
CREATE TABLE dome_Bogies_items (
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
INSERT INTO dome_Bogies_items VALUES (1,"torqueTarget","float",12,"",0.054,"","","");
INSERT INTO dome_Bogies_items VALUES (2,"torqueMeasured","float",12,"",0.054,"","","");
INSERT INTO dome_Bogies_items VALUES (3,"currentTarget","float",12,"",0.054,"","","");
INSERT INTO dome_Bogies_items VALUES (4,"currentMeasured","float",12,"",0.054,"","","");
INSERT INTO dome_Bogies_items VALUES (5,"rpmTarget","float",12,"",0.054,"","","");
INSERT INTO dome_Bogies_items VALUES (6,"rpmMeasured","float",12,"",0.054,"","","");
INSERT INTO dome_Bogies_items VALUES (7,"temperature","float",12,"",0.054,"","","");
INSERT INTO dome_Bogies_items VALUES (8,"status","long",12,"",0.054,"","","");
