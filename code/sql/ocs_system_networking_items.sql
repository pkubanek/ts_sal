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
INSERT INTO ocs_system_networking_items VALUES (1,"subsystem","string",128,"",0.054,"","","");
INSERT INTO ocs_system_networking_items VALUES (2,"mac","string",32,"",0.054,"","","");
INSERT INTO ocs_system_networking_items VALUES (3,"ip","long",4,"",0.054,"","","");
INSERT INTO ocs_system_networking_items VALUES (4,"rx","long",6,"",0.054,"","","");
INSERT INTO ocs_system_networking_items VALUES (5,"tx","long",6,"",0.054,"","","");
