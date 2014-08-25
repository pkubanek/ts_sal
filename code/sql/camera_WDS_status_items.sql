DROP TABLE IF EXISTS camera_WDS_status_items;
CREATE TABLE camera_WDS_status_items (
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
INSERT INTO camera_WDS_status_items VALUES (1,"flag","long",20,"none",0.054,"none","Science and corner rafts","Error flags[");
INSERT INTO camera_WDS_status_items VALUES (2,"REB_ID"," unsignedshort",1,"none",0.054,"none","Cryostat","Raft Electronics Board ID");
