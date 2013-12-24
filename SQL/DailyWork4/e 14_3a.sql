use ap;

go
create view FirstInvoice_v as
	select VendorID, MIN(InvoiceDate) as FirstInvoiceDate 
	from Invoices
	group by VendorID;
	
	


