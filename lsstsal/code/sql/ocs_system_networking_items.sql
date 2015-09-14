DROP TABLE IF EXISTS ocs_system_networking_items;
CREATE TABLE ocs_system_networking_items (
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
INSERT INTO ocs_system_networking_items VALUES (1,"ip","long",4,"",1,"","","");
INSERT INTO ocs_system_networking_items VALUES (2,"rx","long",6,"",1,"","","");
INSERT INTO ocs_system_networking_items VALUES (3,"tx","long",6,"",1,"","","");
