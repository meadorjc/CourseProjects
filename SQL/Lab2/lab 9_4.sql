use MyGuitarShop;
select OrderID, 
		OrderDate, 
		dateadd(day, 2, orderdate) as ApproxShipDate, 
		Shipdate,
		datediff(day, orderdate, shipdate) as DaysToShip
from Orders
where OrderDate >= '2012-03-01' AND OrderDate < '2012-04-01'