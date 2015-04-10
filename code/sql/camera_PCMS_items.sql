DROP TABLE IF EXISTS camera_PCMS_items;
CREATE TABLE camera_PCMS_items (
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
INSERT INTO camera_PCMS_items VALUES (1,"FPGA_current","float",1,"",11,"","","");
INSERT INTO camera_PCMS_items VALUES (2,"Low_current","float",1,"",11,"","","");
INSERT INTO camera_PCMS_items VALUES (3,"Clock_current","float",1,"",11,"","","");
INSERT INTO camera_PCMS_items VALUES (4,"OD_current","float",1,"",11,"","","");
INSERT INTO camera_PCMS_items VALUES (5,"Bias_current","float",1,"",11,"","","");
INSERT INTO camera_PCMS_items VALUES (6,"FPGA_Status","short",1,"",11,"","","");
INSERT INTO camera_PCMS_items VALUES (7,"Low_Status","short",1,"",11,"","","");
INSERT INTO camera_PCMS_items VALUES (8,"Clock_Status","short",1,"",11,"","","");
INSERT INTO camera_PCMS_items VALUES (9,"OD_Status","short",1,"",11,"","","");
INSERT INTO camera_PCMS_items VALUES (10,"Bias_Status","short",1,"",11,"","","");
INSERT INTO camera_PCMS_items VALUES (11,"FPGA_voltage","float",1,"",11,"","","");
INSERT INTO camera_PCMS_items VALUES (12,"Low_voltage","float",1,"",11,"","","");
INSERT INTO camera_PCMS_items VALUES (13,"Clock_voltage","float",1,"",11,"","","");
INSERT INTO camera_PCMS_items VALUES (14,"OD_voltage","float",1,"",11,"","","");
INSERT INTO camera_PCMS_items VALUES (15,"Bias_voltage","float",1,"",11,"","","");
INSERT INTO camera_PCMS_items VALUES (16,"REB_ID","short",1,"",11,"","","");
