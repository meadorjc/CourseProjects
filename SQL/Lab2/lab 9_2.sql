/*Caleb Meador meadorjc at gmail.com*/
use MyGuitarShop;

select orderdate, year(orderdate) as "year", 
	day(orderdate) as "day", 
	dateadd(day,30,orderdate) as "dateadded"
from Orders