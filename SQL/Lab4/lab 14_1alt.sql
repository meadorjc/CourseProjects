/*Caleb Meador meadorjc at gmail.com*/
declare @ProductCount int;

select @ProductCount = 
	(select count(p.productID) as ProductCount
	from PRoducts p join OrderItems oi
	on p.ProductID = oi.OrderID
	group by p.ProductID);
go
Select ProductID, @ProductCount
from products
where (if @ProductCount > 7 
		print 'The number of products is greater than or equal to 7'
	else
		print 'The number of products is less than 7';)
