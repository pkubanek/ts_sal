DROP TABLE IF EXISTS tcs_kernel_PointingLog_items;
CREATE TABLE tcs_kernel_PointingLog_items (
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
INSERT INTO tcs_kernel_PointingLog_items VALUES (1,"Ra","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingLog_items VALUES (2,"Dec","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingLog_items VALUES (3,"Wavel","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingLog_items VALUES (4,"Roll","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingLog_items VALUES (5,"Pitch","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingLog_items VALUES (6,"Casspa","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingLog_items VALUES (7,"Xr","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingLog_items VALUES (8,"Yr","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingLog_items VALUES (9,"Fl","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingLog_items VALUES (10,"Temp","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingLog_items VALUES (11,"Press","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingLog_items VALUES (12,"Humid","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingLog_items VALUES (13,"Tlr","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingLog_items VALUES (14,"Rcorr","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingLog_items VALUES (15,"Aux","float",3,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingLog_items VALUES (16,"Marked","long",1,"",0.054,"","","");
