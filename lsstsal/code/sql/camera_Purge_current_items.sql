DROP TABLE IF EXISTS camera_Purge_current_items;
CREATE TABLE camera_Purge_current_items (
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
INSERT INTO camera_Purge_current_items VALUES (1,"Heater_current","float",1,"Amp",0.017,"","Camera body","Heater settings");
INSERT INTO camera_Purge_current_items VALUES (2,"Heaters","float",1,"Amp",0.017,"","Camera body","Heaters");
