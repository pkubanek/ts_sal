DROP TABLE IF EXISTS tcs_kernel_Site_items;
CREATE TABLE tcs_kernel_Site_items (
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
INSERT INTO tcs_kernel_Site_items VALUES (1,"tai","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (2,"delat","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (3,"delut","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (4,"ttmtat","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (5,"elongm","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (6,"latm","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (7,"hm","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (8,"xpm","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (9,"ypm","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (10,"Ttmtai","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (11,"Elong","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (12,"Lat","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (13,"Uau","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (14,"Vau","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (15,"Ukm","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (16,"Vkm","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (17,"Diurab","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (18,"T0","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (19,"St0","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (20,"Tt0","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (21,"Ttj","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (22,"Amprms","float",21,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (23,"Aoprms","float",15,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (24,"Refa","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (25,"Refb","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (26,"Daz","float",1,"",0.054,"","","");
