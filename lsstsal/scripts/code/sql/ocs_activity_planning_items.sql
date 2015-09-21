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
INSERT INTO ocs_activity_planning_items VALUES (1,"activity_code","long",1,"",0.054,"","","");
INSERT INTO ocs_activity_planning_items VALUES (2,"duration","double",1,"",0.054,"","","");
