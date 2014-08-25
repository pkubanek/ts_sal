DROP TABLE IF EXISTS camera_BEE_biases_items;
CREATE TABLE camera_BEE_biases_items (
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
INSERT INTO camera_BEE_biases_items VALUES (1,"reset","long",201,"",0.054,"","","");
INSERT INTO camera_BEE_biases_items VALUES (2,"operate","long",201,"",0.054,"","","");
INSERT INTO camera_BEE_biases_items VALUES (3,"substrate","long",201,"",0.054,"","","");
