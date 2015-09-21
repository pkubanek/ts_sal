DROP TABLE IF EXISTS tcs_kernel_TrackRefSys_items;
CREATE TABLE tcs_kernel_TrackRefSys_items (
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
INSERT INTO tcs_kernel_TrackRefSys_items VALUES (1,"tdbj","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_TrackRefSys_items VALUES (2,"amprms","float",21,"",0.054,"","","");
INSERT INTO tcs_kernel_TrackRefSys_items VALUES (3,"ae2mt","float",9,"",0.054,"","","");
INSERT INTO tcs_kernel_TrackRefSys_items VALUES (4,"hm","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_TrackRefSys_items VALUES (5,"tlat","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_TrackRefSys_items VALUES (6,"diurab","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_TrackRefSys_items VALUES (7,"refa","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_TrackRefSys_items VALUES (8,"refb","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_TrackRefSys_items VALUES (9,"temp","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_TrackRefSys_items VALUES (10,"press","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_TrackRefSys_items VALUES (11,"humid","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_TrackRefSys_items VALUES (12,"tlr","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_TrackRefSys_items VALUES (13,"wavel","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_TrackRefSys_items VALUES (14,"sst","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_TrackRefSys_items VALUES (15,"cst","float",1,"",0.054,"","","");
