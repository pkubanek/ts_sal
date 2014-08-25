DROP TABLE IF EXISTS enclosure_Application_items;
CREATE TABLE enclosure_Application_items (
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
INSERT INTO enclosure_Application_items VALUES (1,"Demand","float",4,"",0.054,"","","");
INSERT INTO enclosure_Application_items VALUES (2,"Position","float",4,"",0.054,"","","");
INSERT INTO enclosure_Application_items VALUES (3,"Error","float",4,"",0.054,"","","");
INSERT INTO enclosure_Application_items VALUES (4,"Status","string",16,"",0.054,"","","");
