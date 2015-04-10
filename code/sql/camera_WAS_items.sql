DROP TABLE IF EXISTS camera_WAS_items;
CREATE TABLE camera_WAS_items (
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
INSERT INTO camera_WAS_items VALUES (1,"FPGACheckSum","long",2,"",11,"","","");
INSERT INTO camera_WAS_items VALUES (2,"Board_current","float",4,"",11,"","","");
INSERT INTO camera_WAS_items VALUES (3,"CABAC_MUX","long",4,"",11,"","","");
INSERT INTO camera_WAS_items VALUES (4,"CCD_ID","short",1,"",11,"","","");
INSERT INTO camera_WAS_items VALUES (5,"Board_ID","short",1,"",11,"","","");
INSERT INTO camera_WAS_items VALUES (6,"CCD_temp","float",1,"",11,"","","");
INSERT INTO camera_WAS_items VALUES (7,"Board_temp","float",12,"",11,"","","");
INSERT INTO camera_WAS_items VALUES (8,"Board_voltage","float",4,"",11,"","","");
INSERT INTO camera_WAS_items VALUES (9,"REB_ID","short",1,"",11,"","","");
