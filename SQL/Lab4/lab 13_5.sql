/*Caleb Meador meadorjc at gmail.com*/


GO
create view ProductSummary as
	select ProductName, count(OrderID) as OrderCount,
	SUM(ItemTotal) as OrderTotal
	from OrderItemProducts 
	group by productname;