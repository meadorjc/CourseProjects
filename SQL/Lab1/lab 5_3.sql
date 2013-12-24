/*
3.	Write a SELECT statement that returns one row for each customer that has orders with these columns:
The EmailAddress column from the Customers table
The sum of the item price in the OrderItems table multiplied by the quantiy in the OrderItems table
The sum of the discount amount column in the OrderItems table multiplied by the quantiy in the OrderItems table
Sort the result set in descending sequence by the item price total for each customer.
*/

use MyGuitarShop;
select EmailAddress,
		/*ItemPrice*Quantity as TotalPrice,
		DiscountAmount*Quantity as TotalDiscount*/
		SUM(itemprice*quantity) as TotalPrice,
		SUM(discountamount*quantity) as TotalDiscount
from Customers as c
join Orders as o
on c.CustomerID = o.CustomerID
join OrderItems as oi
on o.OrderID = oi.OrderID
group by EmailAddress
order by TotalPrice desc


