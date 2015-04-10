DROP TABLE IF EXISTS dome_Louvers_items;
CREATE TABLE dome_Louvers_items (
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
INSERT INTO dome_Louvers_items VALUES (1,"raw","long",72,"",0.054,"","","");
INSERT INTO dome_Louvers_items VALUES (2,"calibrated","float",72,"",0.054,"","","");
INSERT INTO dome_Louvers_items VALUES (3,"temperature","float",72,"",0.054,"","","");
INSERT INTO dome_Louvers_items VALUES (4,"windSpeed","float",72,"",0.054,"","","");
