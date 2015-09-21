DROP TABLE IF EXISTS camera_Cryo_pressure_items;
CREATE TABLE camera_Cryo_pressure_items (
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
INSERT INTO camera_Cryo_pressure_items VALUES (1,"Intake_pressure","float",2,"Pa",0.010,"none","Utility room","Compressor intake  pressure");
INSERT INTO camera_Cryo_pressure_items VALUES (2,"Pre_expansion_pressure","float",2,"Pa",0.010,"none","Cryostat or utility trunk","Pre-expansion C4 pressure");
INSERT INTO camera_Cryo_pressure_items VALUES (3,"Post_expansion_pressure","float",2,"Pa",0.010,"none","Cryostat or utility trunk","Post-evaporator pressure");
