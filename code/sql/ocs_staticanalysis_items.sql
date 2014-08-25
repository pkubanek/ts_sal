DROP TABLE IF EXISTS ocs_staticanalysis_items;
CREATE TABLE ocs_staticanalysis_items (
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
INSERT INTO ocs_staticanalysis_items VALUES (1,"subsystem","string",128,"",0.054,"","","");
INSERT INTO ocs_staticanalysis_items VALUES (2,"part","string",128,"",0.054,"","","");
INSERT INTO ocs_staticanalysis_items VALUES (3,"start","float",1,"",0.054,"","","");
INSERT INTO ocs_staticanalysis_items VALUES (4,"end","float",1,"",0.054,"","","");
INSERT INTO ocs_staticanalysis_items VALUES (5,"result","long",1,"",0.054,"","","");
INSERT INTO ocs_staticanalysis_items VALUES (6,"action","long",1,"",0.054,"","","");
INSERT INTO ocs_staticanalysis_items VALUES (7,"actuuid","string",32,"",0.054,"","","");
