/*Caleb Meador meadorjc at gmail.com*/
select CustomerID, ShipLine1 
from CustomerAddresses
where CustomerID = 8;


update CustomerAddresses
set ShipLine1 = '1990 Westwood Blvd'
where CustomerID  = 8;

select CustomerID, ShipLine1 
from CustomerAddresses
where CustomerID = 8;