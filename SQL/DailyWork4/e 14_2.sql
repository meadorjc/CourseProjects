/*Caleb Meador meadorjc at gmail.com*/
use AP;

select VendorID, MIN(InvoiceDate) as FirstInvoiceDate
into #FirstInvoice
from Invoices 
group by VendorID;


select VendorName, FirstInvoiceDate, InvoiceTotal
from invoices i join #FirstInvoice 
on (i.VendorID = #FirstInvoice.VendorID and 
i.InvoiceDate = #FirstInvoice.FirstInvoiceDate)
join Vendors v on v.VendorID = #FirstInvoice.VendorID
order by VendorName, FirstInvoiceDate;
	