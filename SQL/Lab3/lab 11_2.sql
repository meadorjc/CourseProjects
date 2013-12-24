use master;

IF DB_ID('Test_MyWebDB') IS NOT NULL
	DROP DATABASE Test_MyWebDB
GO
create database Test_MyWebDB
GO
use Test_MyWebDB
go

create table Users (
	UserID  int	identity not null primary key,
	EmailAddress varchar(40) NOT NULL,
	FirstName	varchar(30) NOT NULL,
	LastName	varchar(30) not null);

create table Products (
	ProductID int primary key identity,
	ProductName varchar(30) not null );
	
create table Downloads (
	DownloadID int primary key identity,
	UserID int foreign key REFERENCES Users(UserID),
	DownloadDate date not null,
	[FileName] varchar(40) not null,
	ProductID int foreign key REFERENCES Products(ProductID));

create index IX_DownloadID on Downloads(DownloadID);
create index IX_FileName on Downloads([FileName]);
