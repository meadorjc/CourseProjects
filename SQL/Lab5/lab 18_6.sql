use myguitarshop;

go
create schema admin;

go
alter schema admin transfer dbo.addresses;

alter user roberthalliday 
	with default_schema = admin;

grant execute, insert, delete, update
on schema::admin
to roberthalliday;

