use ap;
select VendorName, 
	COUNT(ili.AccountNo) as TotalAccountCount
from Vendors as v 
join Invoices as i
on v.VendorID = i.VendorID
join InvoiceLineItems as ili
on i.InvoiceID = ili.InvoiceID
group by VendorName
having COUNT(ili.AccountNo) > 1
order by TotalAccountCount desc


