DROP TABLE IF EXISTS Cold_flow_items;
CREATE TABLE Cold_flow_items (
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
INSERT INTO Cold_flow_items VALUES (1,"Intake_flow","float",6,"lps",0.054,"","");
