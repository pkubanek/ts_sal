DROP TABLE IF EXISTS ocs_scheduler_program_items;
CREATE TABLE ocs_scheduler_program_items (
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
INSERT INTO ocs_scheduler_program_items VALUES (1,"id","long",1,"",0.054,"","","");
INSERT INTO ocs_scheduler_program_items VALUES (2,"priority","long",1,"",0.054,"","","");
INSERT INTO ocs_scheduler_program_items VALUES (3,"status","long",1,"",0.054,"","","");
INSERT INTO ocs_scheduler_program_items VALUES (4,"completion","float",1,"",0.054,"","","");
