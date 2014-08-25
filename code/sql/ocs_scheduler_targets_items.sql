DROP TABLE IF EXISTS ocs_scheduler_targets_items;
CREATE TABLE ocs_scheduler_targets_items (
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
INSERT INTO ocs_scheduler_targets_items VALUES (1,"ra","double",10,"",0.054,"","","");
INSERT INTO ocs_scheduler_targets_items VALUES (2,"dec","double",10,"",0.054,"","","");
INSERT INTO ocs_scheduler_targets_items VALUES (3,"catid","double",10,"",0.054,"","","");
INSERT INTO ocs_scheduler_targets_items VALUES (4,"airmass","double",10,"",0.054,"","","");
INSERT INTO ocs_scheduler_targets_items VALUES (5,"rotangle","double",10,"",0.054,"","","");
INSERT INTO ocs_scheduler_targets_items VALUES (6,"filter","long",10,"",0.054,"","","");
INSERT INTO ocs_scheduler_targets_items VALUES (7,"numexp","long",10,"",0.054,"","","");
