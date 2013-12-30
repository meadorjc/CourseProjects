/*Caleb Meador meadorjc at gmail.com*/
USE MyGuitarShop;

GO
CREATE VIEW OrderItemProducts as
	select Orders.OrderID, orderdate, TaxAmount, ShipDate,
			ItemPrice, DiscountAmount, ItemPrice-DiscountAmount as FinalPrice,
			Quantity, (ItemPrice-DiscountAmount)*Quantity as ItemTotal,ProductName
	from Orders join OrderItems
	on orders.OrderID = OrderItems.OrderID
	join Products on Products.ProductID = OrderItems.ProductID;