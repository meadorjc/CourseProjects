use MyGuitarShop;
select ProductName, Listprice
from products
where listprice > (select avg(listprice) 
					from Products)
Order by Listprice desc;