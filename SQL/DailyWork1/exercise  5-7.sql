SELECT VendorName,
	count(*) as LineItemCount, 
	sum(InvoiceLineItemAmount) as LineItemSum,
	AccountDescription
from Vendors as v join Invoices as i
on v.VendorId = i.VendorID
join InvoiceLineItems as ili
on i.InvoiceId = ili.InvoiceId
join GLAccounts as gla
on ili.AccountNo = gla.AccountNo
group by VendorName, AccountDescription
order by VendorName, AccountDescription
