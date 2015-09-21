DROP TABLE IF EXISTS tcs_kernel_TimeKeeper_items;
CREATE TABLE tcs_kernel_TimeKeeper_items (
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
INSERT INTO tcs_kernel_TimeKeeper_items VALUES (1,"Tai","float",1,"",20,"","","");
INSERT INTO tcs_kernel_TimeKeeper_items VALUES (2,"Tt","float",1,"",20,"","","");
INSERT INTO tcs_kernel_TimeKeeper_items VALUES (3,"Cst","float",1,"",20,"","","");
INSERT INTO tcs_kernel_TimeKeeper_items VALUES (4,"Sst","float",1,"",20,"","","");
INSERT INTO tcs_kernel_TimeKeeper_items VALUES (5,"Dcst","float",1,"",20,"","","");
INSERT INTO tcs_kernel_TimeKeeper_items VALUES (6,"Dsst","float",1,"",20,"","","");
