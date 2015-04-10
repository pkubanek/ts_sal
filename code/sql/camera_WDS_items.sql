DROP TABLE IF EXISTS camera_WDS_items;
CREATE TABLE camera_WDS_items (
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
INSERT INTO camera_WDS_items VALUES (1,"flag","long",20,"",11,"","","");
INSERT INTO camera_WDS_items VALUES (2,"Timing_parameter","long",10,"",11,"","","");
INSERT INTO camera_WDS_items VALUES (3,"REB_ID","short",1,"",11,"","","");
