DROP TABLE IF EXISTS Filter_status_items;
CREATE TABLE Filter_status_items (
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
INSERT INTO Filter_status_items VALUES (1,"Filter_presence","short",10,"none",0.054,"","");
INSERT INTO Filter_status_items VALUES (2,"Brake_status","short",1,"none",0.054,"","");
INSERT INTO Filter_status_items VALUES (3,"Clamp_status","short",5,"none",0.054,"","");
