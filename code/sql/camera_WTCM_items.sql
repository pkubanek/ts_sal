DROP TABLE IF EXISTS camera_WTCM_items;
CREATE TABLE camera_WTCM_items (
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
INSERT INTO camera_WTCM_items VALUES (1,"parameters","float",10,"none",0.1,"","");
