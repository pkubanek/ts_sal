DROP TABLE IF EXISTS Cluster_Encoder_items;
CREATE TABLE Cluster_Encoder_items (
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
INSERT INTO Cluster_Encoder_items VALUES (1,"Image_mean","float",3216,"none",0.054,"","");
INSERT INTO Cluster_Encoder_items VALUES (2,"Image_SD","float",3216,"none",0.054,"","");
INSERT INTO Cluster_Encoder_items VALUES (3,"Overscan_mean","float",3216,"none",0.054,"","");
INSERT INTO Cluster_Encoder_items VALUES (4,"Overscan_SD","float",3216,"none",0.054,"","");
INSERT INTO Cluster_Encoder_items VALUES (5,"PSF","float",9648,"none",0.054,"","");
