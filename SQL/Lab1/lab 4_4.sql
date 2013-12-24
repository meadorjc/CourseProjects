use MyGuitarShop
select LastName, FirstName, OrderDate, ProductName, ItemPrice, DiscountAmount, Quantity
from Customers as c
join Orders as o
on c.CustomerID = o.CustomerID
join OrderItems as oi
on o.OrderID = oi.OrderID
join Products as p
on oi.ProductID = p.ProductID
order by LastName, OrderDate, ProductName;
