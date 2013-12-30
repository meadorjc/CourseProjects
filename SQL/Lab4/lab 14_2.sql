/*Caleb Meador meadorjc at gmail.com*/
declare @ProdCount int;
declare @AvgListPrice money;


select @ProdCount  = 
	count(*)
	from Products;

select @AvgListPrice =  
	avg(itemprice)
	from OrderItems;
	
if @ProdCount > 7 
	begin 
		print 'ProdCount: ' 
		+ convert(varchar, @ProdCount, 1) ;
		print 'AvgListPrice: $'
		+convert(varchar, @AvgListPrice, 1);
	end
else
	print 'The number of products is less than 7';
