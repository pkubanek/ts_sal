DROP TABLE IF EXISTS command_response_items;
CREATE TABLE command_response_items (
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
INSERT INTO command_response_items VALUES (1,"cmdID","long",1,"",0.1,"","");
INSERT INTO command_response_items VALUES (2,"timeout","long",1,"",0.1,"","");
INSERT INTO command_response_items VALUES (3,"repeat","short",1,"",0.1,"","");
INSERT INTO command_response_items VALUES (4,"submits","short",1,"",0.1,"","");