DROP TABLE IF EXISTS camera_Purge_items;
CREATE TABLE camera_Purge_items (
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
INSERT INTO camera_Purge_items VALUES (1,"Accelerometer","float",6,"",11,"","","");
INSERT INTO camera_Purge_items VALUES (2,"Heater_current","float",1,"",11,"","","");
INSERT INTO camera_Purge_items VALUES (3,"Heaters","float",1,"",11,"","","");
INSERT INTO camera_Purge_items VALUES (4,"Trunk_Flow_meter","float",1,"",11,"","","");
INSERT INTO camera_Purge_items VALUES (5,"Body_Flow_meter","float",1,"",11,"","","");
INSERT INTO camera_Purge_items VALUES (6,"Microphone","long",1,"",11,"","","");
INSERT INTO camera_Purge_items VALUES (7,"Blower_setting","float",1,"",11,"","","");
INSERT INTO camera_Purge_items VALUES (8,"Blower_speed","float",1,"",11,"","","");
INSERT INTO camera_Purge_items VALUES (9,"Valves","long",1,"",11,"","","");
INSERT INTO camera_Purge_items VALUES (10,"Trunk_Temp","float",1,"",11,"","","");
INSERT INTO camera_Purge_items VALUES (11,"Body_Temp","float",1,"",11,"","","");
INSERT INTO camera_Purge_items VALUES (12,"Valve_setting","long",1,"",11,"","","");
