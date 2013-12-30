/*Caleb Meador meadorjc at gmail.com*/
create view Top10PaidInvoices as
	select TOP 10 VendorName, MAX(InvoiceDate) as LastInvoice, SUM(invoiceTotal) as SumOfInvoices /*these become columns in the view!! */
	from Vendors v join Invoices i
	on v.VendorID =i.VEndorID
	where InvoiceTotal - CreditTotal - PaymentTotal = 0
	group by VendorName
	order by SumOfInvoices desc