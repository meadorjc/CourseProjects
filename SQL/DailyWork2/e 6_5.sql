/*Caleb Meador meadorjc at gmail.com*/
select  VendorName,
		i.InvoiceID,
		InvoiceSequence,
		InvoiceLineItemAmount
from Vendors as v
join Invoices as i
on v.VendorID = i.VendorID
join InvoiceLIneItems as ili
on i.InvoiceID = ili.InvoiceID
where i.InvoiceID in 
		(select InvoiceID
		from InvoiceLineItems
		where InvoiceSequence > 1)
