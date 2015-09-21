DROP TABLE IF EXISTS camera_Cold_items;
CREATE TABLE camera_Cold_items (
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
INSERT INTO camera_Cold_items VALUES (1,"Ion_pump","float",4,"",11,"","","");
INSERT INTO camera_Cold_items VALUES (2,"Heater_current","float",6,"",11,"","","");
INSERT INTO camera_Cold_items VALUES (3,"Intake_flow","float",6,"",11,"","","");
INSERT INTO camera_Cold_items VALUES (4,"Compressor_load","float",6,"",11,"","","");
INSERT INTO camera_Cold_items VALUES (5,"Intake_pressure","float",6,"",11,"","","");
INSERT INTO camera_Cold_items VALUES (6,"Pre_expansion_pressure","float",6,"",11,"","","");
INSERT INTO camera_Cold_items VALUES (7,"Post_expansion_pressure","float",6,"",11,"","","");
INSERT INTO camera_Cold_items VALUES (8,"Compressor_speed","float",6,"",11,"","","");
INSERT INTO camera_Cold_items VALUES (9,"Dischaarge_pressure","float",6,"",11,"","","");
INSERT INTO camera_Cold_items VALUES (10,"Discharge_temp","float",6,"",11,"","","");
INSERT INTO camera_Cold_items VALUES (11,"Valve_status","short",6,"",11,"","","");
INSERT INTO camera_Cold_items VALUES (12,"Mech_pump","short",4,"",11,"","","");
INSERT INTO camera_Cold_items VALUES (13,"RGA","long",10,"",11,"","","");
INSERT INTO camera_Cold_items VALUES (14,"Flow_interlock","short",6,"",11,"","","");
INSERT INTO camera_Cold_items VALUES (15,"UtilityRoom_temperature","float",1,"",11,"","","");
INSERT INTO camera_Cold_items VALUES (16,"Intake_temp","float",6,"",11,"","","");
INSERT INTO camera_Cold_items VALUES (17,"Pre_expansion_temp","float",6,"",11,"","","");
INSERT INTO camera_Cold_items VALUES (18,"Post_expansion_temp","float",6,"",11,"","","");
INSERT INTO camera_Cold_items VALUES (19,"Return_temp","float",6,"",11,"","","");
INSERT INTO camera_Cold_items VALUES (20,"Vacuum_gauge","float",5,"",11,"","","");
INSERT INTO camera_Cold_items VALUES (21,"Heater_voltage","float",6,"",11,"","","");
