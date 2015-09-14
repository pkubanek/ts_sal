DROP TABLE IF EXISTS camera_WAS_checksum_items;
CREATE TABLE camera_WAS_checksum_items (
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
INSERT INTO camera_WAS_checksum_items VALUES (1,"FPGACheckSum","long",2,"none",2.31E-05,"","","FPGA Configuration checksum (2");
INSERT INTO camera_WAS_checksum_items VALUES (2,"REB_ID"," unsignedshort",1,"none",0.054,"none","Cryostat","Raft Electronics Board ID");
