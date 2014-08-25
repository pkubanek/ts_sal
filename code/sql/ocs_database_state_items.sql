DROP TABLE IF EXISTS ocs_database_state_items;
CREATE TABLE ocs_database_state_items (
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
INSERT INTO ocs_database_state_items VALUES (1,"name","string",64,"",0.054,"","","");
INSERT INTO ocs_database_state_items VALUES (2,"table","string",64,"",0.054,"","","");
INSERT INTO ocs_database_state_items VALUES (3,"status","long",32,"",0.054,"","","");
INSERT INTO ocs_database_state_items VALUES (4,"recin","long",32,"",0.054,"","","");
INSERT INTO ocs_database_state_items VALUES (5,"recout","long",32,"",0.054,"","","");
INSERT INTO ocs_database_state_items VALUES (6,"capacity","long",32,"",0.054,"","","");
INSERT INTO ocs_database_state_items VALUES (7,"lastrep","long",32,"",0.054,"","","");
