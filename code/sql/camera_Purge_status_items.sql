DROP TABLE IF EXISTS camera_Purge_status_items;
CREATE TABLE camera_Purge_status_items (
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
INSERT INTO camera_Purge_status_items VALUES (1,"Valves","long",1,"none",0.017,"","Camera body","Valve statuses");
