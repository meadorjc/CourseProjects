/*Caleb Meador meadorjc at gmail.com*/
use MyGuitarShop;

select DateAdded, cast(dateadded as date) as "Date", 
				cast(dateadded as time) as "Time", 
				cast(dateadded as char(7)) as MonthDay
from products