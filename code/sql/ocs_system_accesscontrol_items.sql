DROP TABLE IF EXISTS ocs_system_accesscontrol_items;
CREATE TABLE ocs_system_accesscontrol_items (
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
INSERT INTO ocs_system_accesscontrol_items VALUES (1,"accept","long",128,"",0.054,"","","");
INSERT INTO ocs_system_accesscontrol_items VALUES (2,"deny","long",128,"",0.054,"","","");
