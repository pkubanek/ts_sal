DROP TABLE IF EXISTS system_Computer_status_items;
CREATE TABLE system_Computer_status_items (
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
INSERT INTO system_Computer_status_items VALUES (1,"Raw","long",16,"",1,"","","");
INSERT INTO system_Computer_status_items VALUES (2,"Calibrated","float",32,"",1,"","","");
