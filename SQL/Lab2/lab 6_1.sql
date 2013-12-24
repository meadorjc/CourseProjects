use MyGuitarShop;

Select distinct CategoryName
from categories c 
where categoryID IN (select categoryID from Products)
order by CategoryName