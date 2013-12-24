use MyGuitarShop;

GO
create view CustomerAddresses as
	select c.CustomerID, EmailAddress, LastName, 
	FirstName, ba.Line1 as BillLine1, ba.Line2 as BillLine2,
	ba.City as BillCity, ba.State as BillState, ba.ZipCode as BillZip,
	sa.Line1 as ShipLine1, sa.Line2 as ShipLine2, sa.City as ShipCity, 
	sa.State as ShipState, sa.ZipCode as ShipZip
	from Customers c join Addresses ba
	on c.BillingAddressID = ba.AddressID
	join Addresses sa
	on c.ShippingAddressID = sa.AddressID;