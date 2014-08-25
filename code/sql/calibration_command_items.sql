DROP TABLE IF EXISTS calibration_command_items;
CREATE TABLE calibration_command_items (
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
INSERT INTO calibration_command_items VALUES (1,"cmdID","long",1,"",0.1,"","");
