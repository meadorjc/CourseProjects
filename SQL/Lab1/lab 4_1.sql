Use MyGuitarShop;
select CategoryName, ProductName, ListPrice
from Categories as c
join Products as p
on c.CategoryID = p.CategoryID
order by CategoryName, ProductName asc;
