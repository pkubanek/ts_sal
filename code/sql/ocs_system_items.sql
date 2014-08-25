DROP TABLE IF EXISTS ocs_system_items;
CREATE TABLE ocs_system_items (
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
INSERT INTO ocs_system_items VALUES (1,"health","long",500,"",0.054,"","","");
INSERT INTO ocs_system_items VALUES (2,"power","long",500,"",0.054,"","","");
INSERT INTO ocs_system_items VALUES (3,"thermal","long",500,"",0.054,"","","");
