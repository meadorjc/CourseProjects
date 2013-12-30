/*Caleb Meador meadorjc at gmail.com*/
begin try
		insert into Categories
		values ('Guitars');
		print 'Record was inserted';
end try
begin catch
		print 'FAILURE: Record was not inserted';
		print 'Violation of UNIQUE KEY constraint "UQ__Categori__8517B2E021015720". 
			Cannot insert duplicate key in object "dbo.Categories". The duplicate 
			key value is (Guitars).';
end catch;
