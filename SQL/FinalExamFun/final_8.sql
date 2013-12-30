/*Caleb Meador meadorjc at gmail.com*/
USE COLLEGE;

GO
IF OBJECT_ID('studentname_enroll') IS NOT NULL
	DROP VIEW studentname_enroll;
	
GO
CREATE VIEW studentname_enroll as
	(SELECT FIRSTNAME+LASTNAME as STUDENTNAME, classNumber
		from Student 
		left join Enroll on student.stuid = enroll.stuid
		)
		

GO
SELECT studentName, classNumber
	FROM studentname_enroll
	order by studentname asc
	