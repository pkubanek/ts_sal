DROP TABLE IF EXISTS skycam_Application_items;
CREATE TABLE skycam_Application_items (
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
INSERT INTO skycam_Application_items VALUES (1,"Sky_parms","float",32,"",0.054,"","","");
INSERT INTO skycam_Application_items VALUES (2,"Data","float",64,"",0.054,"","","");
INSERT INTO skycam_Application_items VALUES (3,"Error","float",4,"",0.054,"","","");
