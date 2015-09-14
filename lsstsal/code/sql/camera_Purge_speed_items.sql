DROP TABLE IF EXISTS camera_Purge_speed_items;
CREATE TABLE camera_Purge_speed_items (
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
INSERT INTO camera_Purge_speed_items VALUES (1,"Blower_setting","float",1,"Hz",0.017,"","Camera body","Blower speed setting");
INSERT INTO camera_Purge_speed_items VALUES (2,"Blower_speed","float",1,"Hz",0.017,"","Camera body","Blower speed");
