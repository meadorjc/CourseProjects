USE COLLEGE;

GO
IF OBJECT_ID('art_students') IS NOT NULL
	DROP VIEW art_students;
	
GO
CREATE VIEW art_students as
	(SELECT FIRSTNAME+LASTNAME as STUDENTNAME, MAJOR
		from Student 
		left join Enroll on student.stuid = enroll.stuid
		where classNumber LIKE '%ART%')
		

GO
SELECT *
	FROM art_students
	order by studentname asc;