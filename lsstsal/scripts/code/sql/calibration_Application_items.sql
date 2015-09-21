DROP TABLE IF EXISTS calibration_Application_items;
CREATE TABLE calibration_Application_items (
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
INSERT INTO calibration_Application_items VALUES (1,"Demand","float",4,"",0.054,"","","");
INSERT INTO calibration_Application_items VALUES (2,"Position","float",4,"",0.054,"","","");
INSERT INTO calibration_Application_items VALUES (3,"Error","float",4,"",0.054,"","","");
