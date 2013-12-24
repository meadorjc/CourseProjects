use AP;
go 
create schema Admin;
go
alter schema admin transfer dbo.ContactUpdates;
alter user Aaron with default_schema = Admin;
grant select, update, insert, delete, execute on schema :: Admin
to Aaron;