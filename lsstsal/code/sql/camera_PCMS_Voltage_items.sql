DROP TABLE IF EXISTS camera_PCMS_Voltage_items;
CREATE TABLE camera_PCMS_Voltage_items (
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
INSERT INTO camera_PCMS_Voltage_items VALUES (1,"FPGA_voltage","float",1,"none",0.054,"none","Utility trunk","FPGA voltage");
INSERT INTO camera_PCMS_Voltage_items VALUES (2,"Low_voltage","float",1,"none",0.054,"none","Utility trunk","Low voltage");
INSERT INTO camera_PCMS_Voltage_items VALUES (3,"Clock_voltage","float",1,"none",0.054,"none","Utility trunk","Clock voltage");
INSERT INTO camera_PCMS_Voltage_items VALUES (4,"OD_voltage","float",1,"none",0.054,"none","Utility trunk","OD voltage");
INSERT INTO camera_PCMS_Voltage_items VALUES (5,"Bias_voltage","float",1,"none",0.054,"none","Utility trunk","Bias voltage");
INSERT INTO camera_PCMS_Voltage_items VALUES (6,"REB_ID"," unsignedshort",1,"none",0.054,"none","Cryostat","Raft Electronics Board ID");
