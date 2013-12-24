select top 10 VendorName, SUM(PaymentTotal)
AS PaymentSum
from Vendors as v 
join Invoices as i
on v.VendorID = i.VendorID
group by VendorName
order by PaymentSum desc;
