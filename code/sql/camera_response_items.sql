DROP TABLE IF EXISTS camera_response_items;
CREATE TABLE camera_response_items (
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
INSERT INTO camera_response_items VALUES (1,"cmdID","long",1,"",0.1,"","");
INSERT INTO camera_response_items VALUES (2,"ack","string",16,"",0.1,"","");
INSERT INTO camera_response_items VALUES (3,"error","string",16,"",0.1,"","");
INSERT INTO camera_response_items VALUES (4,"timeout","long",1,"",0.1,"","");
INSERT INTO camera_response_items VALUES (5,"repeat","short",1,"",0.1,"","");
INSERT INTO camera_response_items VALUES (6,"submits","short",1,"",0.1,"","");
INSERT INTO camera_response_items VALUES (7,"result","string",64,"",0.1,"","");
