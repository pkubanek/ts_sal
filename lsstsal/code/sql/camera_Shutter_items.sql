DROP TABLE IF EXISTS camera_Shutter_items;
CREATE TABLE camera_Shutter_items (
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
INSERT INTO camera_Shutter_items VALUES (1,"Motor_current","float",2,"",11,"","","");
INSERT INTO camera_Shutter_items VALUES (2,"Open_direction","short",1,"",11,"","","");
INSERT INTO camera_Shutter_items VALUES (3,"Blade_home","short",2,"",11,"","","");
INSERT INTO camera_Shutter_items VALUES (4,"Motor_temp","float",2,"",11,"","","");
INSERT INTO camera_Shutter_items VALUES (5,"Open_profile","float",24,"",11,"","","");
INSERT INTO camera_Shutter_items VALUES (6,"Close_profile","float",24,"",11,"","","");
