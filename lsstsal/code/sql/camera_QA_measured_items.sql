DROP TABLE IF EXISTS camera_QA_measured_items;
CREATE TABLE camera_QA_measured_items (
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
INSERT INTO camera_QA_measured_items VALUES (1,"metric1","float",132,"",0.054,"","","");
INSERT INTO camera_QA_measured_items VALUES (2,"metric2","float",132,"",0.054,"","","");
INSERT INTO camera_QA_measured_items VALUES (3,"metric3","float",132,"",0.054,"","","");
INSERT INTO camera_QA_measured_items VALUES (4,"metric4","float",132,"",0.054,"","","");
