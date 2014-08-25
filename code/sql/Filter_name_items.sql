DROP TABLE IF EXISTS Filter_name_items;
CREATE TABLE Filter_name_items (
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
INSERT INTO Filter_name_items VALUES (1,"Filter_online","string",32,"none",0.054,"","");
