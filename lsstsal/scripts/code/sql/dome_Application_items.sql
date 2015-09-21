DROP TABLE IF EXISTS dome_Application_items;
CREATE TABLE dome_Application_items (
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
INSERT INTO dome_Application_items VALUES (1,"azTarget","float",1,"",0.054,"","","");
INSERT INTO dome_Application_items VALUES (2,"azPosition","float",1,"",0.054,"","","");
INSERT INTO dome_Application_items VALUES (3,"azError","float",1,"",0.054,"","","");
INSERT INTO dome_Application_items VALUES (4,"elevTarget","float",1,"",0.054,"","","");
INSERT INTO dome_Application_items VALUES (5,"elevPosition","float",1,"",0.054,"","","");
INSERT INTO dome_Application_items VALUES (6,"elevError","float",1,"",0.054,"","","");
INSERT INTO dome_Application_items VALUES (7,"scrTarget","float",1,"",0.054,"","","");
INSERT INTO dome_Application_items VALUES (8,"scrPosition","float",1,"",0.054,"","","");
INSERT INTO dome_Application_items VALUES (9,"scrError","float",1,"",0.054,"","","");
INSERT INTO dome_Application_items VALUES (10,"lvTarget","float",72,"",0.054,"","","");
INSERT INTO dome_Application_items VALUES (11,"lvPosition","float",72,"",0.054,"","","");
INSERT INTO dome_Application_items VALUES (12,"lvError","float",72,"",0.054,"","","");
