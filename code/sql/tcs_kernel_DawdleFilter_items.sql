DROP TABLE IF EXISTS tcs_kernel_DawdleFilter_items;
CREATE TABLE tcs_kernel_DawdleFilter_items (
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
INSERT INTO tcs_kernel_DawdleFilter_items VALUES (1,"Bypass","long",1,"",0.054,"","","");
INSERT INTO tcs_kernel_DawdleFilter_items VALUES (2,"T","float",1,"",0.054,"","","");
