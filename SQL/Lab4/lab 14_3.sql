declare @count int;

select @count = 20;

print 'Common Factors of 10 and 20';

while @count > 0
	begin
		if (20 % @count = 0 and 10 % @count = 0 and @count <> 10)
		print @count;
		select @count = @count-1;
	end 		
