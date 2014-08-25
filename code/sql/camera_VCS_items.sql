DROP TABLE IF EXISTS camera_VCS_items;
CREATE TABLE camera_VCS_items (
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
INSERT INTO camera_VCS_items VALUES (1,"control","float",10,"none",0.1,"","");
INSERT INTO camera_VCS_items VALUES (2,"pressure","float",10,"none",0.1,"","");
