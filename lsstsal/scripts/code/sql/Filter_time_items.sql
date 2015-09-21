DROP TABLE IF EXISTS Filter_time_items;
CREATE TABLE Filter_time_items (
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
INSERT INTO Filter_time_items VALUES (1,"Change_Duration","float",1,"sec",0.054,"","");
