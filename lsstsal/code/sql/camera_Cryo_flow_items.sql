DROP TABLE IF EXISTS camera_Cryo_flow_items;
CREATE TABLE camera_Cryo_flow_items (
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
INSERT INTO camera_Cryo_flow_items VALUES (1,"Intake_flow","float",2,"lps",0.010,"none","Utility room","Compressor intake  flow");
