DROP TABLE IF EXISTS camera_GAS_items;
CREATE TABLE camera_GAS_items (
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
INSERT INTO camera_GAS_items VALUES (1,"algorithm","string",32,"none",0.1,"","");
INSERT INTO camera_GAS_items VALUES (2,"parameters","float",10,"none",0.1,"","");
INSERT INTO camera_GAS_items VALUES (3,"sampleData_00","float",25,"none",0.1,"","");
INSERT INTO camera_GAS_items VALUES (4,"sampleData_01","float",25,"none",0.1,"","");
INSERT INTO camera_GAS_items VALUES (5,"sampleData_10","float",25,"none",0.1,"","");
INSERT INTO camera_GAS_items VALUES (6,"sampleData_11","float",25,"none",0.1,"","");
