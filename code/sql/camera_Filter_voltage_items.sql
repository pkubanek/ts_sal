DROP TABLE IF EXISTS camera_Filter_voltage_items;
CREATE TABLE camera_Filter_voltage_items (
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
INSERT INTO camera_Filter_voltage_items VALUES (1,"Latch_voltage","float",10,"Volt",2.31E-04,"none","Camera body","Carousel: 10 actuator voltages");
INSERT INTO camera_Filter_voltage_items VALUES (2,"Clamp_voltage","float",5,"Volt",2.31E-04,"none","Camera body","Auto: Actuator voltages");
