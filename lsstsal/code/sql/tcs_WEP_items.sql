DROP TABLE IF EXISTS tcs_WEP_items;
CREATE TABLE tcs_WEP_items (
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
INSERT INTO tcs_WEP_items VALUES (1,"z_arr1","double",18,"",0.054,"","","");
INSERT INTO tcs_WEP_items VALUES (2,"z_arr2","double",18,"",0.054,"","","");
INSERT INTO tcs_WEP_items VALUES (3,"z_arr3","double",18,"",0.054,"","","");
INSERT INTO tcs_WEP_items VALUES (4,"z_arr4","double",18,"",0.054,"","","");
