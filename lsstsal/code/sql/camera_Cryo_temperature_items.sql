DROP TABLE IF EXISTS camera_Cryo_temperature_items;
CREATE TABLE camera_Cryo_temperature_items (
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
INSERT INTO camera_Cryo_temperature_items VALUES (1,"Cold_temperature","float",3,"Kelvin",0.010,"","","Straps, cryoplate, coldplate (3");
INSERT INTO camera_Cryo_temperature_items VALUES (2,"Cryo_temperature","float",12,"Kelvin",0.010,"none","Cryostat","L3 flange, etc.");
INSERT INTO camera_Cryo_temperature_items VALUES (3,"Intake_temp","float",2,"Celsius",0.010,"none","Utility room","Compressor intake temperature");
INSERT INTO camera_Cryo_temperature_items VALUES (4,"Pre_expansion_temp","float",2,"Celsius",0.010,"none","Cryostat or utility trunk","Pre-expansion C4 temperature");
INSERT INTO camera_Cryo_temperature_items VALUES (5,"Post_expansion_temp","float",2,"Celsius",0.010,"none","Cryostat or utility trunk","Post-evaporator temperature");
INSERT INTO camera_Cryo_temperature_items VALUES (6,"Return_temp","float",2,"Celsius",0.010,"none","Cryostat or utility trunk","Return line temperature");
