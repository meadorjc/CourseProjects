use MyGuitarShop;

select convert(varchar, orderdate, 101) as "Date", 
		convert(varchar, orderdate, 0) as "DateAndTime", 
		convert(varchar, orderdate, 8) as "Time"
from Orders;