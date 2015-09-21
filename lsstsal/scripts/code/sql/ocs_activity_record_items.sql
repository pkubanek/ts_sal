DROP TABLE IF EXISTS ocs_activity_record_items;
CREATE TABLE ocs_activity_record_items (
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
INSERT INTO ocs_activity_record_items VALUES (1,"activity_code","long",1,"",0.054,"","","");
INSERT INTO ocs_activity_record_items VALUES (2,"result_code","long",1,"",0.054,"","","");
