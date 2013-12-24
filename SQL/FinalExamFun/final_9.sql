use college;
go

if OBJECT_ID('spFacultySchedule') IS NOT NULL
	DROP proc spFacultySchedule;

go
create proc spFacultySchedule
as
select faculty.name, schedule, room
	from FACULTY
	left join class
	on faculty.facid = class.facid;
/*NOTE: 2 Faculty are named Smith; must use left join to show both, though
	one of the Smith professors doesn't have a class, so appears null. */


go

exec spFacultySchedule;