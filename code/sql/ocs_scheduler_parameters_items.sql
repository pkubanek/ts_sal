DROP TABLE IF EXISTS ocs_scheduler_parameters_items;
CREATE TABLE ocs_scheduler_parameters_items (
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
INSERT INTO ocs_scheduler_parameters_items VALUES (1,"algorithm","string",32,"",0.054,"","","");
INSERT INTO ocs_scheduler_parameters_items VALUES (2,"p1","string",32,"",0.054,"","","");
INSERT INTO ocs_scheduler_parameters_items VALUES (3,"p2","string",32,"",0.054,"","","");
INSERT INTO ocs_scheduler_parameters_items VALUES (4,"p3","string",32,"",0.054,"","","");
INSERT INTO ocs_scheduler_parameters_items VALUES (5,"p4","string",32,"",0.054,"","","");
