/*Caleb Meador meadorjc at gmail.com*/
use master
go
if DB_ID('Membership') is not null
	drop database Membership
go
create database Membership
go
use Membership
go
create table Individuals (
IndividualID int identity not null primary key,
FirstName varchar(20) not null,
LastName varchar(20) not null,
[Address] varchar(100) not null,
Phone varchar(14) null)
go
create table Groups (
GroupID int identity not null primary key,
GroupName varchar(40) not null,
Dues money not null default 0 check (Dues >= 0))
go
create table GroupMembership (
GroupID int not null references Groups (GroupID),
IndividualID int not null references Individuals (IndividualID))
go
create clustered index IX_GroupID
	on GroupMembership (GroupID)
create index IX_IndividualID
	on GroupMembership (IndividualID)
go
alter table Individuals
	add DuesPaid bit not null default 0