DROP TABLE IF EXISTS ocs_operator_log_items;
CREATE TABLE ocs_operator_log_items (
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
INSERT INTO ocs_operator_log_items VALUES (1,"opid","long",1,"",0.054,"","","");
INSERT INTO ocs_operator_log_items VALUES (2,"stationid","long",1,"",0.054,"","","");
INSERT INTO ocs_operator_log_items VALUES (3,"subsystem","string",32,"",0.054,"","","");
INSERT INTO ocs_operator_log_items VALUES (4,"device","string",32,"",0.054,"","","");
INSERT INTO ocs_operator_log_items VALUES (5,"event","string",128,"",0.054,"","","");
