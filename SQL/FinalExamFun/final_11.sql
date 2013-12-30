/*Caleb Meador meadorjc at gmail.com*/
use COLLEGE;

	CREATE ROLE Students;

Grant SELECT
TO Students;

go



DECLARE @SQLstatement varchar(256),
		@LoginName varchar(128),
		@TempPassword varchar(8);

DECLARE Login_Cursor CURSOR
DYNAMIC
FOR
	SELECT LastName+FirstName AS LoginName
	from Student;
	

OPEN Login_Cursor;
FETCH NEXT FROM Login_Cursor
	INTO @LoginName;
WHILE @@FETCH_STATUS = 0
	BEGIN
		SET @TempPassword = left(@loginname, 4);
		SET @SQLstatement = 'create login ' + @LoginName + ' with password = ''' + @TempPassword + ''',default_database = COLLEGE';
		EXEC(@SQLstatement);
		SET @SQLstatement = 'CREATE USER ' + @LoginName + ' ' + 
						  'FOR LOGIN ' + @LoginName;
		EXEC(@SQLstatement);
		SET @SQLstatement = 'ALTER ROLE Students ADD MEMBER ' 
							+ @LoginName;
		EXEC (@SQLstatement);
		FETCH NEXT FROM Login_Cursor
			INTO @LoginName;
	END;
CLOSE Login_Cursor;

DEALLOCATE Login_Cursor;
