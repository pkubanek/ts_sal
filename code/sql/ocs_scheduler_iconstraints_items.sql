DROP TABLE IF EXISTS ocs_scheduler_iconstraints_items;
CREATE TABLE ocs_scheduler_iconstraints_items (
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
INSERT INTO ocs_scheduler_iconstraints_items VALUES (1,"type","string",32,"",0.054,"","","");
INSERT INTO ocs_scheduler_iconstraints_items VALUES (2,"minval","string",32,"",0.054,"","","");
INSERT INTO ocs_scheduler_iconstraints_items VALUES (3,"maxval","string",32,"",0.054,"","","");
