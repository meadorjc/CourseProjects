/*Caleb Meador meadorjc at gmail.com*/
use college;
go

if OBJECT_ID('spStudentCourse') IS NOT NULL
	DROP proc spStudentCourse;

go
create proc spStudentCourse
as
select class.classNumber, firstName+lastname as studentname
	from Class 
	left join enroll
	on class.classNumber = enroll.classNumber
	left join student
	on enroll.stuid = student.stuid
	order by classNumber asc;
/*note: 1 course has no students; hence NULL*/
go

exec spStudentCourse;