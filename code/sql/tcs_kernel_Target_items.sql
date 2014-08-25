DROP TABLE IF EXISTS tcs_kernel_Target_items;
CREATE TABLE tcs_kernel_Target_items (
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
INSERT INTO tcs_kernel_Target_items VALUES (1,"site","string",128,"",0.054,"","","");
INSERT INTO tcs_kernel_Target_items VALUES (2,"t0","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Target_items VALUES (3,"az","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Target_items VALUES (4,"el","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Target_items VALUES (5,"azdot","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Target_items VALUES (6,"eldot","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Target_items VALUES (7,"Wavel","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Target_items VALUES (8,"XOffset","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Target_items VALUES (9,"YOffset","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Target_items VALUES (10,"OffSys","string",128,"",0.054,"","","");
INSERT INTO tcs_kernel_Target_items VALUES (11,"focalplaneX","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Target_items VALUES (12,"focalplaneY","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Target_items VALUES (13,"Temp","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Target_items VALUES (14,"Press","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Target_items VALUES (15,"Humid","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Target_items VALUES (16,"TLR","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Target_items VALUES (17,"Tai","float",1,"",0.054,"","","");
