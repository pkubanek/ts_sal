DROP TABLE IF EXISTS tcs_kernel_PointingControl_items;
CREATE TABLE tcs_kernel_PointingControl_items (
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
INSERT INTO tcs_kernel_PointingControl_items VALUES (1,"RollFilter","string",32,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingControl_items VALUES (2,"PitchFilter","string",32,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingControl_items VALUES (3,"AGuide","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingControl_items VALUES (4,"BGuide","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingControl_items VALUES (5,"ALocal","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingControl_items VALUES (6,"BLocal","float",1,"",0.054,"","","");
