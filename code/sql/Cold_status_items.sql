DROP TABLE IF EXISTS Cold_status_items;
CREATE TABLE Cold_status_items (
  num	int,
  item	char(32),
  type  char(32),
  size  int,
  units char(32),
  freq  float,
  range char(32),
  comment char(128),
  PRIMARY KEY (num)
);
INSERT INTO Cold_status_items VALUES (1,"Valve_status","short",6,"none",0.054,"","");
INSERT INTO Cold_status_items VALUES (2,"Mech_pump","short",4,"none",0.054,"","");
INSERT INTO Cold_status_items VALUES (3,"RGA","long",10,"??",0.054,"","");
INSERT INTO Cold_status_items VALUES (4,"Flow_interlock","short",6,"none",0.054,"","");
