DROP TABLE IF EXISTS system_Hardware_revision_history_items;
CREATE TABLE system_Hardware_revision_history_items (
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
INSERT INTO system_Hardware_revision_history_items VALUES (1,"Part","string",32,"",0.054,"","","");
INSERT INTO system_Hardware_revision_history_items VALUES (2,"Reason","string",32,"",0.054,"","","");
INSERT INTO system_Hardware_revision_history_items VALUES (3,"Version","long",3,"",0.054,"","","");
