DROP TABLE IF EXISTS PCMS_Current_items;
CREATE TABLE PCMS_Current_items (
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
INSERT INTO PCMS_Current_items VALUES (1,"FPGA_current","float",1,"none",0.054,"","");
INSERT INTO PCMS_Current_items VALUES (2,"Low_current","float",1,"none",0.054,"","");
INSERT INTO PCMS_Current_items VALUES (3,"Clock_current","float",1,"none",0.054,"","");
INSERT INTO PCMS_Current_items VALUES (4,"OD_current","float",1,"none",0.054,"","");
INSERT INTO PCMS_Current_items VALUES (5,"Bias_current","float",1,"none",0.054,"","");
INSERT INTO PCMS_Current_items VALUES (6,"REB_ID"," unsignedshort",1,"",0.054,"","");
