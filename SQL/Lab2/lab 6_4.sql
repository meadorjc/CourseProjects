/*Caleb Meador meadorjc at gmail.com*/
use MyGuitarShop;
select EmailAddress, max(ordertotal) as topOrderTotal
from (select c.EmailAddress, oi.orderID, sum((oi.ItemPrice-oi.DiscountAmount)*oi.Quantity) as ordertotal
	  from Customers c
	  join orders o
	  on c.customerID=o.CustomerID
	  join OrderItems oi
	  on o.OrderID = oi.OrderID
	  group by c.emailaddress, oi.orderid
	  ) as topcustomer 

group by EmailAddress


	  
		
		
		
		
		
		
		

