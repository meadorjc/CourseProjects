select InvoiceNumber,
	InvoiceTotal-PaymentTotal-CreditTotal as BalanceDue,
	InvoiceDueDate

from Invoices
where InvoiceTotal-PaymentTotal-CreditTotal > 0 and
	InvoiceDueDate < DateAdd(day, 30, getDate());