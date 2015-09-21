DROP TABLE IF EXISTS tcs_AOCS_items;
CREATE TABLE tcs_AOCS_items (
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
INSERT INTO tcs_AOCS_items VALUES (1,"result","string",32,"",0.054,"","","");
