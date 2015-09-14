DROP TABLE IF EXISTS camera_PCMS_Status_items;
CREATE TABLE camera_PCMS_Status_items (
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
INSERT INTO camera_PCMS_Status_items VALUES (1,"FPGA_Status","short",1,"none",0.054,"none","Utility trunk","FPGA Status");
INSERT INTO camera_PCMS_Status_items VALUES (2,"Low_Status","short",1,"none",0.054,"none","Utility trunk","Low Status");
INSERT INTO camera_PCMS_Status_items VALUES (3,"Clock_Status","short",1,"none",0.054,"none","Utility trunk","Clock Status");
INSERT INTO camera_PCMS_Status_items VALUES (4,"OD_Status","short",1,"none",0.054,"none","Utility trunk","OD Status");
INSERT INTO camera_PCMS_Status_items VALUES (5,"Bias_Status","short",1,"none",0.054,"none","Utility trunk","Bias Status");
INSERT INTO camera_PCMS_Status_items VALUES (6,"REB_ID"," unsignedshort",1,"none",0.054,"none","Cryostat","Raft Electronics Board ID");
