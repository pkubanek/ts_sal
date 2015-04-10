DROP TABLE IF EXISTS tcs_kernel_FK5Target_items;
CREATE TABLE tcs_kernel_FK5Target_items (
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
INSERT INTO tcs_kernel_FK5Target_items VALUES (1,"ra","float",1,"",20,"","","");
INSERT INTO tcs_kernel_FK5Target_items VALUES (2,"dec","float",1,"",20,"","","");
INSERT INTO tcs_kernel_FK5Target_items VALUES (3,"equinox","float",1,"",20,"","","");
INSERT INTO tcs_kernel_FK5Target_items VALUES (4,"epoc","float",1,"",20,"","","");
INSERT INTO tcs_kernel_FK5Target_items VALUES (5,"pmRA","float",1,"",20,"","","");
INSERT INTO tcs_kernel_FK5Target_items VALUES (6,"pmDec","float",1,"",20,"","","");
INSERT INTO tcs_kernel_FK5Target_items VALUES (7,"parallax","float",1,"",20,"","","");
INSERT INTO tcs_kernel_FK5Target_items VALUES (8,"rv","float",1,"",20,"","","");
