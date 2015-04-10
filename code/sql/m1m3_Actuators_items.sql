DROP TABLE IF EXISTS m1m3_Actuators_items;
CREATE TABLE m1m3_Actuators_items (
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
INSERT INTO m1m3_Actuators_items VALUES (1,"setpoint","long",120,"",20,"","","");
INSERT INTO m1m3_Actuators_items VALUES (2,"position","long",120,"",20,"","","");
INSERT INTO m1m3_Actuators_items VALUES (3,"error","long",120,"",20,"","","");
INSERT INTO m1m3_Actuators_items VALUES (4,"status","long",120,"",20,"","","");
INSERT INTO m1m3_Actuators_items VALUES (5,"cyltemp","float",120,"",20,"","","");
INSERT INTO m1m3_Actuators_items VALUES (6,"envtemp","float",120,"",20,"","","");
INSERT INTO m1m3_Actuators_items VALUES (7,"lvdtcorr","float",120,"",20,"","","");
INSERT INTO m1m3_Actuators_items VALUES (8,"pressure","float",120,"",20,"","","");
