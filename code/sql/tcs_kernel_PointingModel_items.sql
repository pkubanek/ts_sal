DROP TABLE IF EXISTS tcs_kernel_PointingModel_items;
CREATE TABLE tcs_kernel_PointingModel_items (
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
INSERT INTO tcs_kernel_PointingModel_items VALUES (1,"Model","long",30,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingModel_items VALUES (2,"Coeffv","float",100,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingModel_items VALUES (3,"Nterml","long",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingModel_items VALUES (4,"Ntermx","long",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingModel_items VALUES (5,"Nterms","long",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingModel_items VALUES (6,"Coeff1","string",32,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingModel_items VALUES (7,"Coeff2","string",32,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingModel_items VALUES (8,"Coeff3","string",32,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingModel_items VALUES (9,"Coeff4","string",32,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingModel_items VALUES (10,"Coeff5","string",32,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingModel_items VALUES (11,"Coeff6","string",32,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingModel_items VALUES (12,"Coeff7","string",32,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingModel_items VALUES (13,"Coeff8","string",32,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingModel_items VALUES (14,"Coeff9","string",32,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingModel_items VALUES (15,"Cofor1","string",32,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingModel_items VALUES (16,"Cofor2","string",32,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingModel_items VALUES (17,"Cofor3","string",32,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingModel_items VALUES (18,"Cofor4","string",32,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingModel_items VALUES (19,"Cofor5","string",32,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingModel_items VALUES (20,"Cofor6","string",32,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingModel_items VALUES (21,"Cofor7","string",32,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingModel_items VALUES (22,"Cofor8","string",32,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingModel_items VALUES (23,"Cofor9","string",32,"",0.054,"","","");
