DROP TABLE IF EXISTS camera_Cold_status_items;
CREATE TABLE camera_Cold_status_items (
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
INSERT INTO camera_Cold_status_items VALUES (1,"Valve_status","short",6,"none",0.000,"none","Utility trunk","Vacuum valve status published on change");
INSERT INTO camera_Cold_status_items VALUES (2,"Mech_pump","short",4,"none",0.010,"none","Utility trunk","Status (2 cryostat, 2 heat exch)");
INSERT INTO camera_Cold_status_items VALUES (3,"RGA","long",10,"??",0.010,"none","Cryostat","Two RGAs, 5 gasses each");
INSERT INTO camera_Cold_status_items VALUES (4,"Flow_interlock","short",6,"none",0.010,"none","Utility room","Compressor water flow interlock");
