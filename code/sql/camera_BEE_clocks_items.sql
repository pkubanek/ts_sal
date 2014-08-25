DROP TABLE IF EXISTS camera_BEE_clocks_items;
CREATE TABLE camera_BEE_clocks_items (
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
INSERT INTO camera_BEE_clocks_items VALUES (1,"serial_1A","long",201,"none",0.1,"","");
INSERT INTO camera_BEE_clocks_items VALUES (2,"serial_2A","long",201,"none",0.1,"","");
INSERT INTO camera_BEE_clocks_items VALUES (3,"serial_3A","long",201,"none",0.1,"","");
INSERT INTO camera_BEE_clocks_items VALUES (4,"serial_1B","long",201,"none",0.1,"","");
INSERT INTO camera_BEE_clocks_items VALUES (5,"serial_2B","long",201,"none",0.1,"","");
INSERT INTO camera_BEE_clocks_items VALUES (6,"serial_3B","long",201,"none",0.1,"","");
INSERT INTO camera_BEE_clocks_items VALUES (7,"parallel_1A","long",201,"none",0.1,"","");
INSERT INTO camera_BEE_clocks_items VALUES (8,"parallel_1B","long",201,"none",0.1,"","");
INSERT INTO camera_BEE_clocks_items VALUES (9,"parallel_2A","long",201,"none",0.1,"","");
INSERT INTO camera_BEE_clocks_items VALUES (10,"parallel_2B","long",201,"none",0.1,"","");
