DROP TABLE IF EXISTS camera_Cryo_items;
CREATE TABLE camera_Cryo_items (
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
INSERT INTO camera_Cryo_items VALUES (1,"Heater_current","float",6,"",11,"","","");
INSERT INTO camera_Cryo_items VALUES (2,"Intake_flow","float",2,"",11,"","","");
INSERT INTO camera_Cryo_items VALUES (3,"Flow_interlock","short",2,"",11,"","","");
INSERT INTO camera_Cryo_items VALUES (4,"Compressor","float",1,"",11,"","","");
INSERT INTO camera_Cryo_items VALUES (5,"Intake_pressure","float",2,"",11,"","","");
INSERT INTO camera_Cryo_items VALUES (6,"Pre_expansion_pressure","float",2,"",11,"","","");
INSERT INTO camera_Cryo_items VALUES (7,"Post_expansion_pressure","float",2,"",11,"","","");
INSERT INTO camera_Cryo_items VALUES (8,"Compressor_speed","float",2,"",11,"","","");
INSERT INTO camera_Cryo_items VALUES (9,"Dischaarge_pressure","float",2,"",11,"","","");
INSERT INTO camera_Cryo_items VALUES (10,"Discharge_temp","float",2,"",11,"","","");
INSERT INTO camera_Cryo_items VALUES (11,"Cold_temperature","float",3,"",11,"","","");
INSERT INTO camera_Cryo_items VALUES (12,"Cryo_temperature","float",12,"",11,"","","");
INSERT INTO camera_Cryo_items VALUES (13,"Intake_temp","float",2,"",11,"","","");
INSERT INTO camera_Cryo_items VALUES (14,"Pre_expansion_temp","float",2,"",11,"","","");
INSERT INTO camera_Cryo_items VALUES (15,"Post_expansion_temp","float",2,"",11,"","","");
INSERT INTO camera_Cryo_items VALUES (16,"Return_temp","float",2,"",11,"","","");
INSERT INTO camera_Cryo_items VALUES (17,"Heater_voltage","float",6,"",11,"","","");
