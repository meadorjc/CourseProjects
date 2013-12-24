/*
6.	Write a SELECT statement that answers this question: What is the total amount ordered for each product? Return these columns:
The product name from the Products table
The total amount for each product in the OrderItems table (Hint: You can calculate the total amount by subtracting the discount amount 
from the item price and then multiplying it by the quantity)
Use the WITH ROLLUP operator to include a row that gives the grand total.
*/

use MyguitarShop;

select ProductName,
		Sum((ItemPrice-DiscountAmount)*quantity) as TotalAmount
from Products as p
join OrderItems as oi
on p.ProductID = oi.ProductID
group by ProductName with ROLLUP
