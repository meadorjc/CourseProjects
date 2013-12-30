/*Caleb Meador meadorjc at gmail.com*/
USE MyGuitarShop;

declare @dynamicsql varchar(255);
declare @loginname varchar(128);
declare @password char(8);

declare log_cursor cursor
dynamic
for
	select firstname + lastname as loginname from Administrators;

open log_cursor;
fetch next from log_cursor 
	into @loginname;
while @@fetch_status = 0
begin
	set @password = 'temp'
	set @dynamicsql = 'create Login'
					  +@loginname
					  +'with password = '
					  + @password 
					  + ', default_database = myguitarshop;'
					  + ' create user '
					  + @loginname
					  + ' for login ' 
					  + @loginname + '; ' 
					  + 'alter role orderentry add member '
					  + @loginname;
	exec (@dynamicsql);
	fetch next from log_cursor
		into @loginname
end