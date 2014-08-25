DROP TABLE IF EXISTS camera_Filter_status_items;
CREATE TABLE camera_Filter_status_items (
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
INSERT INTO camera_Filter_status_items VALUES (1,"Filter_presence","short",10,"none",2.31E-04,"none","Camera body","FCS: 10 filter presence sensors");
INSERT INTO camera_Filter_status_items VALUES (2,"Brake_status","short",1,"none",2.31E-04,"none","Camera body","Carousel: Brake sensor");
INSERT INTO camera_Filter_status_items VALUES (3,"Clamp_status","short",5,"none",2.31E-04,"none","Camera body","Auto: Clamp locking sensors");
