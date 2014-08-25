DROP TABLE IF EXISTS Filter_voltage_items;
CREATE TABLE Filter_voltage_items (
  num	int,
  item	char(32),
  type  char(32),
  size  int,
  units char(32),
  freq  float,
  range char(32),
  comment char(128),
  PRIMARY KEY (num)
);
INSERT INTO Filter_voltage_items VALUES (1,"Latch_voltage","float",10,"Volt",0.054,"","");
INSERT INTO Filter_voltage_items VALUES (2,"Clamp_voltage","float",5,"Volt",0.054,"","");
