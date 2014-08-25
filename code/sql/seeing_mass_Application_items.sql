DROP TABLE IF EXISTS seeing_mass_Application_items;
CREATE TABLE seeing_mass_Application_items (
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
INSERT INTO seeing_mass_Application_items VALUES (1,"Demand","float",2,"",0.054,"","","");
INSERT INTO seeing_mass_Application_items VALUES (2,"Position","float",2,"",0.054,"","","");
INSERT INTO seeing_mass_Application_items VALUES (3,"Error","float",2,"",0.054,"","","");
INSERT INTO seeing_mass_Application_items VALUES (4,"Status_1","string",128,"",0.054,"","","");
INSERT INTO seeing_mass_Application_items VALUES (5,"Status_2","string",128,"",0.054,"","","");
INSERT INTO seeing_mass_Application_items VALUES (6,"Status_3","string",128,"",0.054,"","","");
INSERT INTO seeing_mass_Application_items VALUES (7,"Status_4","string",128,"",0.054,"","","");
INSERT INTO seeing_mass_Application_items VALUES (8,"Status_5","string",128,"",0.054,"","","");
INSERT INTO seeing_mass_Application_items VALUES (9,"Status_6","string",128,"",0.054,"","","");
INSERT INTO seeing_mass_Application_items VALUES (10,"Status_7","string",128,"",0.054,"","","");
INSERT INTO seeing_mass_Application_items VALUES (11,"Status_8","string",128,"",0.054,"","","");
INSERT INTO seeing_mass_Application_items VALUES (12,"Status_9","string",128,"",0.054,"","","");
INSERT INTO seeing_mass_Application_items VALUES (13,"Status_10","string",128,"",0.054,"","","");
INSERT INTO seeing_mass_Application_items VALUES (14,"Status_11","string",128,"",0.054,"","","");
INSERT INTO seeing_mass_Application_items VALUES (15,"Status_12","string",128,"",0.054,"","","");
INSERT INTO seeing_mass_Application_items VALUES (16,"Status_13","string",128,"",0.054,"","","");
INSERT INTO seeing_mass_Application_items VALUES (17,"Status_14","string",128,"",0.054,"","","");
INSERT INTO seeing_mass_Application_items VALUES (18,"Status_15","string",128,"",0.054,"","","");
