DROP TABLE IF EXISTS tcs_command_items;
CREATE TABLE tcs_command_items (
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
INSERT INTO tcs_command_items VALUES (1,"cmdID","long",1,"",0.054,"","","");
