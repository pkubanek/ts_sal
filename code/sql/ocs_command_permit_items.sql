DROP TABLE IF EXISTS ocs_command_permit_items;
CREATE TABLE ocs_command_permit_items (
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
INSERT INTO ocs_command_permit_items VALUES (1,"subsystem","string",128,"",0.054,"","","");
INSERT INTO ocs_command_permit_items VALUES (2,"device","string",128,"",0.054,"","","");
INSERT INTO ocs_command_permit_items VALUES (3,"command","string",32,"",0.054,"","","");
INSERT INTO ocs_command_permit_items VALUES (4,"actionmask","long",8,"",0.054,"","","");
