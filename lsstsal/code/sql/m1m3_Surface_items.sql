DROP TABLE IF EXISTS m1m3_Surface_items;
CREATE TABLE m1m3_Surface_items (
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
INSERT INTO m1m3_Surface_items VALUES (1,"Raw","long",1024,"",20,"","","");
INSERT INTO m1m3_Surface_items VALUES (2,"Calibrated","float",1024,"",20,"","","");
