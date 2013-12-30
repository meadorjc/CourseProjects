/*Caleb Meador meadorjc at gmail.com*/
Use MyGuitarShop;

if exists (select db_id('Products_UPDATE'))
	drop trigger Products_UPDATE;
GO

create trigger Products_UPDATE 
	on Products
	after update
as 
	if ((select discountpercent from inserted ) <= 0 or
			(select discountpercent from inserted) > 100)
					throw 50001, 'Discount percent must be between 0 and 100', 1;
				
				

	if (select discountpercent from inserted) >= 0 and 
		(select discountpercent from inserted) < 1
					update Products 
					set discountpercent = (select discountpercent from inserted) * 100
					where  ProductID = (select ProductID from inserted);
		
	
go


UPDATE Products
SET DiscountPercent = -1
WHERE ProductID = 1;
GO


UPDATE Products
SET DiscountPercent = .5
WHERE ProductID = 1;
GO



SELECT ProductID, ProductCode, ProductName, DiscountPercent FROM Products;
