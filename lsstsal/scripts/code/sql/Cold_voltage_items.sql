DROP TABLE IF EXISTS Cold_voltage_items;
CREATE TABLE Cold_voltage_items (
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
INSERT INTO Cold_voltage_items VALUES (1,"Heater_voltage","float",6,"Volt",0.054,"","");