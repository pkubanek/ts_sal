DROP TABLE IF EXISTS camera_Cold_current_items;
CREATE TABLE camera_Cold_current_items (
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
INSERT INTO camera_Cold_current_items VALUES (1,"Ion_pump","float",4,"Amp",0.010,"none","Utility trunk","Ion pump current (3 cryostat, 1 heat exch)");
INSERT INTO camera_Cold_current_items VALUES (2,"Heater_current","float",6,"Amp",0.010,"none","Cryostat","Coldplate heater currents");
