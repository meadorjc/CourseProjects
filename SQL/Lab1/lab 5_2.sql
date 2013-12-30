/*Caleb Meador meadorjc at gmail.com*/
/* 
2.	Write a SELECT statement that returns one row for each category that has products with these columns:
The CategoryName column from the Categories table
The count of the products in the Products table
The list price of the most expensive product in the Products table
Sort the result set so the category with the most products appears first.
*/

use MyGuitarShop;

select CategoryName, Count(*) as ProductCount, Sum(ListPrice) as "List Price"
from Categories as c
join Products as p
on c.CategoryID = p.CategoryID
group by CategoryName
order by ProductCount