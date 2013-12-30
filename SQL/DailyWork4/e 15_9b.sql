/*Caleb Meador meadorjc at gmail.com*/
create trigger NoDuplicates
on testUniqueNulls 
after insert, update as 
begin
	if (select COUNT(*)	from TestUniqueNulls join inserted
		on TestUniqueNulls.NoDupName = inserted.NoDupName) > 1
	begin
		rollback tran;
		throw 50001, 'Duplicate value.', 1;
	end;
end;