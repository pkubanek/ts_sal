DROP TABLE IF EXISTS camera_SDS_status_items;
CREATE TABLE camera_SDS_status_items (
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
INSERT INTO camera_SDS_status_items VALUES (1,"flags"," unsignedlong",20,"none",0.1,"","");
INSERT INTO camera_SDS_status_items VALUES (2,"current","float",80,"none",0.1,"","");
