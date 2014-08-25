DROP TABLE IF EXISTS auxscope_Metrology_items;
CREATE TABLE auxscope_Metrology_items (
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
INSERT INTO auxscope_Metrology_items VALUES (1,"Raw","long",16,"",0.054,"","","");
INSERT INTO auxscope_Metrology_items VALUES (2,"Calibrated","float",16,"",0.054,"","","");
