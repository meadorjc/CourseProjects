use AP;

declare avg_cursor cursor 
static
for
	select vendorName, avg(invoiceTotal) as InvoiceAvg
	from Vendors join Invoices
	on vendors.VendorID=invoices.VendorID
	group by vendorname
	
open avg_cursor;
fetch next from avg_cursor;
while @@fetch_status = 0
	fetch next from avg_cursor;
close avg_cursor;
deallocate avg_cursor;
