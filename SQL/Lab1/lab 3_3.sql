/*Caleb Meador meadorjc at gmail.com*/
select ProductName, ListPrice, DateAdded
from Products
where ListPrice > 500 and ListPrice < 1000
order by DateAdded desc;