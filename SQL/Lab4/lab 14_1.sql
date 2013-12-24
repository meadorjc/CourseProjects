
declare @ProductCount int;

select @ProductCount  = 
	count(ProductID)
	from Products;

if @ProductCount > 7 
	print 'The number of products is greater than or equal to 7'
else
	print 'The number of products is less than 7';
