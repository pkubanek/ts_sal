DROP TABLE IF EXISTS camera_Cluster_Encoder_items;
CREATE TABLE camera_Cluster_Encoder_items (
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
INSERT INTO camera_Cluster_Encoder_items VALUES (1,"Image_mean","float",3216,"",0.054,"","","");
INSERT INTO camera_Cluster_Encoder_items VALUES (2,"Image_SD","float",3216,"",0.054,"","","");
INSERT INTO camera_Cluster_Encoder_items VALUES (3,"Overscan_mean","float",3216,"",0.054,"","","");
INSERT INTO camera_Cluster_Encoder_items VALUES (4,"Overscan_SD","float",3216,"",0.054,"","","");
INSERT INTO camera_Cluster_Encoder_items VALUES (5,"PSF","float",9648,"",0.054,"","","");
