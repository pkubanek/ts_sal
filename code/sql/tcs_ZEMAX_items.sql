DROP TABLE IF EXISTS tcs_ZEMAX_items;
CREATE TABLE tcs_ZEMAX_items (
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
INSERT INTO tcs_ZEMAX_items VALUES (1,"bg_algorithm","string",32,"",0.054,"","","");
INSERT INTO tcs_ZEMAX_items VALUES (2,"exposure","double",1,"",0.054,"","","");
INSERT INTO tcs_ZEMAX_items VALUES (3,"iterations","long",1,"",0.054,"","","");
