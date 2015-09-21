DROP TABLE IF EXISTS camera_CCC_status_items;
CREATE TABLE camera_CCC_status_items (
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
INSERT INTO camera_CCC_status_items VALUES (1,"Image_Status","long",20,"",11,"","","");
INSERT INTO camera_CCC_status_items VALUES (2,"CCS_Status","long",20,"",11,"","","");
