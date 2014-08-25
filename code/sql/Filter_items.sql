DROP TABLE IF EXISTS Filter_items;
CREATE TABLE Filter_items (
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
INSERT INTO Filter_items VALUES (1,"Loader_telemetry","long",1,"??",0.054,"","");
INSERT INTO Filter_items VALUES (2,"REB_ID"," unsignedshort",1,"",0.054,"","");
