/*Caleb Meador meadorjc at gmail.com*/
use master;


IF DB_ID('Membership') IS NOT NULL
	DROP DATABASE Membership
GO

create database Membership
/* #1 */
go
use Membership
go

/* #2 */
create table Individuals (
	IndividualID int identity not null primary key, /*identity starts at 1 and increments at 1 */
	FirstName varchar(20) not null,
	LastName varchar(20) not null,
	[Address] varchar(100) not null,
	Phone varchar(14));

create table Groups (
	GroupID int identity not null primary key, /*automatically clustered dt pk */
	GroupName varchar(50) NOT NULL,
	Dues money not null);


create table GroupMembership (
	GroupID int not null references Groups (GroupID), /*declare cluster bc not pk, fk*/
	IndividualID int not null references Individuals(IndividualID));
/* #3 */
create clustered index IX_GroupID on GroupMembership(GroupID);
create index IX_IndividualID on GroupMembership(IndividualID);  
/*can only have 1 clustered/table; default non-clustered*/


/* #4 page 355 */
alter table Individuals
add DuesPaid bit not null default 0;
