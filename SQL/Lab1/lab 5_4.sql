/*
4.	Write a SELECT statement that returns one row for each customer that has orders with these columns:
The EmailAddress column from the Customers table
A count of the number of orders
The total amount for each order (Hint: First, subtract the discount amount from the price. Then, multiply by the quantity.)
Return only those rows where the customer has more than than 1 order.
Sort the result set in descending sequence by the sum of the line item amounts.
*/

Use MyGuitarShop;
select EmailAddress,
		Count(o.OrderID) as "OrderCount",
		Sum((ItemPrice - DiscountAmount) * quantity) as "TotalOrderAmount"
from Customers as c
join Orders as o
on c.CustomerID = o.CustomerID
join OrderItems as oi
on o.OrderID = oi.OrderID
group by EmailAddress
having Count(o.OrderID) > 1
order by Sum((ItemPrice-DiscountAmount)*quantity) desc
