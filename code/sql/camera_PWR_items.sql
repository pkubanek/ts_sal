DROP TABLE IF EXISTS camera_PWR_items;
CREATE TABLE camera_PWR_items (
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
INSERT INTO camera_PWR_items VALUES (1,"supply_voltage","float",25,"",0.1,"","");
INSERT INTO camera_PWR_items VALUES (2,"current","float",25,"",0.1,"","");
