DROP TABLE IF EXISTS camera_Shutter_model_items;
CREATE TABLE camera_Shutter_model_items (
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
INSERT INTO camera_Shutter_model_items VALUES (1,"Profile_function","string",32,"none",0.054,"none","Camera body","Name of Motion profile configuration");
