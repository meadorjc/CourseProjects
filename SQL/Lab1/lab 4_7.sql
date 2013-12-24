use MyGuitarShop;

select 'Shipped' as ShipStatus, OrderID, OrderDate
from Orders
where Shipdate is not null
union
select 'Not Shipped' as ShipStatus, OrderID, OrderDate
from Orders
where Shipdate is null
order by OrderDate;



