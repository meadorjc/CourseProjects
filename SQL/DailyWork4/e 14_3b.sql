/*Caleb Meador meadorjc at gmail.com*/
use AP;
go
if OBJECT_ID('FirstInvoice_v') is not null
begin
select VendorName, firstInvoiceDate, InvoiceTotal
from Invoices i join FirstInvoice_v fiv
on (i.VendorID = fiv.VendorID and i.InvoiceDate = fiv.Firstinvoicedate)
join vendors v on i.VendorID = v.vendorID	
order by VendorName, FirstInvoiceDate
end 
else
begin
	print 'Create FirstInvoice_v view before using this script.'
end