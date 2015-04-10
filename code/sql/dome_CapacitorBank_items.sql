DROP TABLE IF EXISTS dome_CapacitorBank_items;
CREATE TABLE dome_CapacitorBank_items (
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
INSERT INTO dome_CapacitorBank_items VALUES (1,"setpoint","float",1,"",0.054,"","","");
INSERT INTO dome_CapacitorBank_items VALUES (2,"temperature","float",10,"",0.054,"","","");
INSERT INTO dome_CapacitorBank_items VALUES (3,"charge","float",10,"",0.054,"","","");
INSERT INTO dome_CapacitorBank_items VALUES (4,"chargeRate","float",10,"",0.054,"","","");
INSERT INTO dome_CapacitorBank_items VALUES (5,"status","long",10,"",0.054,"","","");
