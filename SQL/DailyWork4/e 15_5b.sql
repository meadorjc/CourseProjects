/*Caleb Meador meadorjc at gmail.com*/
select VendorName, InvoiceNumber, InvoiceDueDate,
	InvoiceTotal-CreditTotal-PaymentTotal as Balance
from VEndors join invoices on vendors.vendorid=invoices.vendorid
where invoiceid = dbo.fnunpaidinvoiceid();