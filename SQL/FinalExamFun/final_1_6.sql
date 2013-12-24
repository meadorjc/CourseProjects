USE [master]

Go
IF DB_ID('COLLEGE') IS NOT NULL
	DROP DATABASE College

Create database COLLEGE
Go

Use [COLLEGE]
go

create table Student(
	stuid		char(5) NOT NULL PRIMARY KEY,
	lastName	varchar(20) NOT NULL,
	firstName	varchar(20) NOT NULL,
	major		varchar(20) NOT NULL, 
	credits 	int NOT NULL
)

GO
INSERT [STUDENT] (STUID, LASTNAME, FIRSTNAME, MAJOR, CREDITS) 
	VALUES ('S1001', 'Smith', 'Tom', 'History',	90)
INSERT [STUDENT] (STUID, LASTNAME, FIRSTNAME, MAJOR, CREDITS) 
	VALUES ('S1002', 'Chin', 'Ann', 'Math',	36)
INSERT [STUDENT] (STUID, LASTNAME, FIRSTNAME, MAJOR, CREDITS) 
	VALUES ('S1005', 'Lee', 'Perry', 'History',	3)
INSERT [STUDENT] (STUID, LASTNAME, FIRSTNAME, MAJOR, CREDITS) 
	VALUES ('S1010', 'Burns', 'Edward', 'Art',	63)
INSERT [STUDENT] (STUID, LASTNAME, FIRSTNAME, MAJOR, CREDITS) 
	VALUES ('S1013', 'McCarthy', 'Owen', 'Math',	0)
INSERT [STUDENT] (STUID, LASTNAME, FIRSTNAME, MAJOR, CREDITS) 
	VALUES ('S1015', 'Jones', 'Mary', 'Math',	42)
INSERT [STUDENT] (STUID, LASTNAME, FIRSTNAME, MAJOR, CREDITS) 
	VALUES ('S1020', 'Rivera', 'Jane', 'CSC',	15)

create table FACULTY (
	facid 	char(4) NOT NULL PRIMARY KEY,
	name	varchar(20) NOT NULL,
	department	varchar(20) NOT NULL,
	[rank] varchar(20) NOT NULL,
	
)

GO
INSERT [FACULTY] (FACID, NAME, DEPARTMENT, RANK)
	VALUES ('F101',	'Adams',	'Art', 'Professor')
INSERT [FACULTY] (FACID, NAME, DEPARTMENT, RANK)
	VALUES ('F105',	'Tanaka',	'CSC', 'Instructor')
INSERT [FACULTY] (FACID, NAME, DEPARTMENT, RANK)
	VALUES ('F110',	'Byrne',	'Math', 'Assistant')
INSERT [FACULTY] (FACID, NAME, DEPARTMENT, RANK)
	VALUES ('F115',	'Smith',	'History', 'Associate')
INSERT [FACULTY] (FACID, NAME, DEPARTMENT, RANK)
	VALUES ('F221',	'Smith',	'CSC', 'Professor')


create table Class(
	classNumber char(7) NOT NULL PRIMARY KEY,
	facid 		char(4) FOREIGN KEY REFERENCES FACULTY(FACID),
	schedule 	varchar(20) NOT NULL, 
	room 		varchar(20) NOT NULL
)

GO
INSERT [CLASS] (CLASSNUMBER, FACID, SCHEDULE, ROOM)
	VALUES ('ART103A',	'F101',	'MWF9',	'H221')
INSERT [CLASS] (CLASSNUMBER, FACID, SCHEDULE, ROOM)
	VALUES ('CSC201A',	'F105',	'TuThF10',	'M110')
INSERT [CLASS] (CLASSNUMBER, FACID, SCHEDULE, ROOM)
	VALUES ('CSC203A',	'F105',	'MThF12',	'M110')
INSERT [CLASS] (CLASSNUMBER, FACID, SCHEDULE, ROOM)
	VALUES ('HST205A',	'F115',	'MWF11',	'H221')
INSERT [CLASS] (CLASSNUMBER, FACID, SCHEDULE, ROOM)
	VALUES ('MTH101B',	'F110',	'MTuTh9',	'H225')
INSERT [CLASS] (CLASSNUMBER, FACID, SCHEDULE, ROOM)
	VALUES ('MTH103C',	'F110',	'MWF11',	'H225')

create table Enroll(
	stuid		char(5) NOT NULL FOREIGN KEY REFERENCES [STUDENT](STUID),
	classNumber	char(7) NOT NULL FOREIGN KEY REFERENCES [CLASS](CLASSNUMBER),
	grade 		char(1) 

)

GO
INSERT [ENROLL] (STUID, CLASSNUMBER, GRADE)
	VALUES ('S1001',	'ART103A',	'A')
INSERT [ENROLL] (STUID, CLASSNUMBER, GRADE)
	VALUES ('S1001',	'HST205A',	'C')
INSERT [ENROLL] (STUID, CLASSNUMBER, GRADE)
	VALUES ('S1002',	'ART103A',	'D')
INSERT [ENROLL] (STUID, CLASSNUMBER, GRADE)
	VALUES ('S1002',	'CSC201A',	'F')
INSERT [ENROLL] (STUID, CLASSNUMBER, GRADE)
	VALUES ('S1002',	'MTH103C',	'B')
INSERT [ENROLL] (STUID, CLASSNUMBER, GRADE)
	VALUES ('S1010',	'ART103A',	NULL)
INSERT [ENROLL] (STUID, CLASSNUMBER, GRADE)
	VALUES ('S1010',	'MTH103C',	NULL)
INSERT [ENROLL] (STUID, CLASSNUMBER, GRADE)
	VALUES ('S1020',	'CSC201A',	'B')
INSERT [ENROLL] (STUID, CLASSNUMBER, GRADE)
	VALUES ('S1020',	'MTH101B',	'A')
	
	
