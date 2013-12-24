use Membership;

drop table GroupMembership;

create table GroupMembership (
GroupID int references Groups (GroupID), 
IndividualID int references Individuals (IndividualID),
unique(GroupID, IndividualID));
