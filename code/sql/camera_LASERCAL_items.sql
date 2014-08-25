DROP TABLE IF EXISTS camera_LASERCAL_items;
CREATE TABLE camera_LASERCAL_items (
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
INSERT INTO camera_LASERCAL_items VALUES (1,"positions","float",10,"none",0.1,"","");
