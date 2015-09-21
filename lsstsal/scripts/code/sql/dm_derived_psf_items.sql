DROP TABLE IF EXISTS dm_derived_psf_items;
CREATE TABLE dm_derived_psf_items (
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
INSERT INTO dm_derived_psf_items VALUES (1,"metric1","double",200,"",0.054,"","","");
INSERT INTO dm_derived_psf_items VALUES (2,"metric2","double",200,"",0.054,"","","");
INSERT INTO dm_derived_psf_items VALUES (3,"metric3","double",200,"",0.054,"","","");
INSERT INTO dm_derived_psf_items VALUES (4,"metric4","double",200,"",0.054,"","","");
INSERT INTO dm_derived_psf_items VALUES (5,"metric5","double",200,"",0.054,"","","");
INSERT INTO dm_derived_psf_items VALUES (6,"metric6","double",200,"",0.054,"","","");
