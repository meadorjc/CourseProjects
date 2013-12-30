/*Caleb Meador meadorjc at gmail.com*/
use ap;

declare @dynamicsql varchar(255);
declare @LoginName varchar(128);
declare @password char(8)


declare NewLogins_Cursor cursor
dynamic
for
	select LoginName from NewLogins;

open NewLogins_cursor;
fetch next from NewLogins_Cursor;
while @@FETCH_STATUS = 0
begin
		set @password = (left(@LoginName, 4) + '9999')
		set @dynamicsql = 'create LoginName =' + @password + ', default_database = AP';
end