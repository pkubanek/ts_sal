DROP TABLE IF EXISTS system_Command_history_items;
CREATE TABLE system_Command_history_items (
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
INSERT INTO system_Command_history_items VALUES (1,"Data","float",16,"",100,"","","");
