DROP TABLE IF EXISTS dm_pointing_wcs_items;
CREATE TABLE dm_pointing_wcs_items (
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
INSERT INTO dm_pointing_wcs_items VALUES (1,"ra","double",200,"",0.054,"","","");
INSERT INTO dm_pointing_wcs_items VALUES (2,"dec","double",200,"",0.054,"","","");
INSERT INTO dm_pointing_wcs_items VALUES (3,"coeff","double",32,"",0.054,"","","");
