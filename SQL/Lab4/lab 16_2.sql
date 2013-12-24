use MyGuitarShop;

declare avg_shipping_amt cursor
static
for
	select LastName, AVG(ShipAmount) as ShipAmountAvg
	from Customers join orders
		on Customers.customerID = orders.CustomerID
	group by lastname;


open avg_shipping_amt;
fetch next from avg_shipping_amt;
while @@FETCH_STATUS = 0
	fetch next from avg_shipping_amt;
close avg_shipping_amt;
deallocate avg_shipping_amt;