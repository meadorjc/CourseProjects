select VendorName, COUNT(*) as InvoiceCount, SUM(InvoiceTotal) as InvoiceSum
from Vendors as v
join Invoices as i
on v.VendorID = i.VendorID
group by VendorName
order by InvoiceCount desc;

