DROP TABLE IF EXISTS PCMS_Voltage_items;
CREATE TABLE PCMS_Voltage_items (
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
INSERT INTO PCMS_Voltage_items VALUES (1,"FPGA_voltage","float",1,"none",0.054,"","");
INSERT INTO PCMS_Voltage_items VALUES (2,"Low_voltage","float",1,"none",0.054,"","");
INSERT INTO PCMS_Voltage_items VALUES (3,"Clock_voltage","float",1,"none",0.054,"","");
INSERT INTO PCMS_Voltage_items VALUES (4,"OD_voltage","float",1,"none",0.054,"","");
INSERT INTO PCMS_Voltage_items VALUES (5,"Bias_voltage","float",1,"none",0.054,"","");
INSERT INTO PCMS_Voltage_items VALUES (6,"REB_ID"," unsignedshort",1,"",0.054,"","");
