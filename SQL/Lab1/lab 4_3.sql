use MyGuitarShop
Select FirstName, LastName, Line1, City, State, ZipCode
from Customers as c
join Addresses as a
on c.CustomerID = a.CustomerID
where ShippingAddressID = AddressID

