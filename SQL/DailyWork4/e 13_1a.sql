/*Caleb Meador meadorjc at gmail.com*/
use ap;
go /*create view has to be the only command unless you use go!! */
create view InvoiceBasic as 
	select VendorName, InvoiceNumber, InvoiceTotal
	from Vendors v join Invoices i
	on v.VendorID = i.VendorID
