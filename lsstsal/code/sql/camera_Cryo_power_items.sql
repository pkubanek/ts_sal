DROP TABLE IF EXISTS camera_Cryo_power_items;
CREATE TABLE camera_Cryo_power_items (
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
INSERT INTO camera_Cryo_power_items VALUES (1,"Compressor","float",1,"Watts",0.010,"none","Utility room","Compressor electrical load");
