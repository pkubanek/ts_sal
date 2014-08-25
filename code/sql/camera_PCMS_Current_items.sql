DROP TABLE IF EXISTS camera_PCMS_Current_items;
CREATE TABLE camera_PCMS_Current_items (
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
INSERT INTO camera_PCMS_Current_items VALUES (1,"FPGA_current","float",1,"none",0.054,"none","Utility trunk","FPGA current");
INSERT INTO camera_PCMS_Current_items VALUES (2,"Low_current","float",1,"none",0.054,"none","Utility trunk","Low current");
INSERT INTO camera_PCMS_Current_items VALUES (3,"Clock_current","float",1,"none",0.054,"none","Utility trunk","Clock current");
INSERT INTO camera_PCMS_Current_items VALUES (4,"OD_current","float",1,"none",0.054,"none","Utility trunk","OD current");
INSERT INTO camera_PCMS_Current_items VALUES (5,"Bias_current","float",1,"none",0.054,"none","Utility trunk","Bias current");
INSERT INTO camera_PCMS_Current_items VALUES (6,"REB_ID"," unsignedshort",1,"none",0.054,"none","Cryostat","Raft Electronics Board ID");
