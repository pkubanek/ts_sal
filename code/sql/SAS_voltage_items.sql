DROP TABLE IF EXISTS SAS_voltage_items;
CREATE TABLE SAS_voltage_items (
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
INSERT INTO SAS_voltage_items VALUES (1,"Board_voltage","float",4,"Volt",0.054,"","");
INSERT INTO SAS_voltage_items VALUES (2,"REB_ID"," unsignedshort",1,"",0.054,"","");
