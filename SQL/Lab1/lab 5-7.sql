/*
7.	Write a SELECT statement that answers this question: Which customers have ordered more than one product? Return these columns:
The email address from the Customers table
The count of distinct products from the customer’s orders
*/

select EmailAddress,
		Count(c.CustomerID) "Number of Products Ordered"
from Customers as c
join Orders as o
on c.CustomerID = o.CustomerID
join OrderItems as oi
on o.OrderID = oi.OrderID
group by EmailAddress
having Count(c.CustomerID) > 1;