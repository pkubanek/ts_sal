DROP TABLE IF EXISTS Prot_items;
CREATE TABLE Prot_items (
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
INSERT INTO Prot_items VALUES (1,"Status","long",2,"Volts",0.054,"","");
