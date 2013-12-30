/*Caleb Meador meadorjc at gmail.com*/
use MyGuitarShop;
select  CategoryName, ProductID
from Products as p
right join Categories as c
on c.CategoryID = p.CategoryID
where ProductID is null;

