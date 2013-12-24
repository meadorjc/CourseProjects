select InvoiceNumber,
	InvoiceTotal-PaymentTotal-CreditTotal as BalanceDue,
	InvoiceDueDate

from Invoices
where InvoiceTotal-PaymentTotal-CreditTotal > 0 and
	InvoiceDueDate < DATEADD(day, -1, cast(CAST(YEAR(GETDATE()) as char(4)) 
	+ '-'
	+ CAST(MONTH(GETDATE())+1 as char(2))
	+ '-01' as date) )