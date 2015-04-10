DROP TABLE IF EXISTS scheduler_nextTarget_items;
CREATE TABLE scheduler_nextTarget_items (
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
INSERT INTO scheduler_nextTarget_items VALUES (1,"ra","double",1,"",0.054,"","","");
INSERT INTO scheduler_nextTarget_items VALUES (2,"dec","double",1,"",0.054,"","","");
INSERT INTO scheduler_nextTarget_items VALUES (3,"skyAngle","double",1,"",0.054,"","","");
INSERT INTO scheduler_nextTarget_items VALUES (4,"filter","string",32,"",0.054,"","","");
INSERT INTO scheduler_nextTarget_items VALUES (5,"expoureTime","double",10,"",0.054,"","","");
INSERT INTO scheduler_nextTarget_items VALUES (6,"numExposures","long",1,"",0.054,"","","");
INSERT INTO scheduler_nextTarget_items VALUES (7,"targetId","long",1,"",0.054,"","","");
