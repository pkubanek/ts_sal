DROP TABLE IF EXISTS auxscope_TCS_items;
CREATE TABLE auxscope_TCS_items (
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
INSERT INTO auxscope_TCS_items VALUES (1,"Raw","long",200,"",0.1,"","");
INSERT INTO auxscope_TCS_items VALUES (2,"Calibrated","float",200,"",0.1,"","");
