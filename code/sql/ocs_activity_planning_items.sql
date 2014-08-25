DROP TABLE IF EXISTS ocs_activity_planning_items;
CREATE TABLE ocs_activity_planning_items (
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
INSERT INTO ocs_activity_planning_items VALUES (1,"type","string",128,"",0.054,"","","");
INSERT INTO ocs_activity_planning_items VALUES (2,"subsystem","string",128,"",0.054,"","","");
INSERT INTO ocs_activity_planning_items VALUES (3,"part","string",128,"",0.054,"","","");
INSERT INTO ocs_activity_planning_items VALUES (4,"supervid","string",128,"",0.054,"","","");
INSERT INTO ocs_activity_planning_items VALUES (5,"uuid","string",32,"",0.054,"","","");
