/*
	Acme Used Cars Database
	Carlyle Flemming
*/
use master
go
if DB_ID('Acme Used Cars') is not null
	drop database [Acme Used Cars]
go
create database [Acme Used Cars]
go
use [Acme Used Cars]
go
create table Vehicle (
InventoryID int not null primary key,
Manufacturer varchar(15) not null,
ModelName varchar(15) not null,
[Year] int not null,
VehicleID varchar(20) not null,
CostValue smallmoney not null)
go
create table Customer (
Number char(6) not null primary key,
Name varchar(80) not null,
InventoryID int not null references Vehicle (InventoryID))
go
create index IX_InventoryID on Customer (InventoryID)
create index IX_Name on Customer (Name)
create index IX_ManufModel on Vehicle (Manufacturer,ModelName)
