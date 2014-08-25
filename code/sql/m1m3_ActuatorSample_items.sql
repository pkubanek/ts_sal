DROP TABLE IF EXISTS m1m3_ActuatorSample_items;
CREATE TABLE m1m3_ActuatorSample_items (
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
INSERT INTO m1m3_ActuatorSample_items VALUES (1,"actuatorID","short",1,"",0.054,"","","");
INSERT INTO m1m3_ActuatorSample_items VALUES (2,"setpoint","long",100,"",0.054,"","","");
INSERT INTO m1m3_ActuatorSample_items VALUES (3,"position","long",100,"",0.054,"","","");
INSERT INTO m1m3_ActuatorSample_items VALUES (4,"error","long",100,"",0.054,"","","");
INSERT INTO m1m3_ActuatorSample_items VALUES (5,"status","long",100,"",0.054,"","","");
