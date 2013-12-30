/*Caleb Meador meadorjc at gmail.com*/
use MyGuitarShop;

select emailaddress, orderid, OrderDate 
from orders o 
join Customers c
on o.CustomerID = c.CustomerID
where orderdate = (select min(orderdate)
		from orders o2
		where o.CustomerID = o2.CustomerID) 
order by EmailAddress, orderID, OrderDate;


