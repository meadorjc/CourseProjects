use MyGuitarShop;
select p1.ProductName, p1.ListPrice
from Products as p1
join Products as p2
on (p1.ProductID <> p2.ProductID)
AND (p1.ListPrice = p2.ListPrice)
order by p1.ProductName