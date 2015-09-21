DROP TABLE IF EXISTS scheduler_interestedProposal_items;
CREATE TABLE scheduler_interestedProposal_items (
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
INSERT INTO scheduler_interestedProposal_items VALUES (1,"targetId","long",1,"",0.054,"","","");
INSERT INTO scheduler_interestedProposal_items VALUES (2,"targetRankPosition","long",1,"",0.054,"","","");
INSERT INTO scheduler_interestedProposal_items VALUES (3,"proposalId","long",1,"",0.054,"","","");
INSERT INTO scheduler_interestedProposal_items VALUES (4,"targetProposalRankValue","double",1,"",0.054,"","","");
INSERT INTO scheduler_interestedProposal_items VALUES (5,"subSequence","string",32,"",0.054,"","","");
INSERT INTO scheduler_interestedProposal_items VALUES (6,"subSequenceNumber","long",1,"",0.054,"","","");
INSERT INTO scheduler_interestedProposal_items VALUES (7,"pairNumber","long",1,"",0.054,"","","");
