/*Caleb Meador meadorjc at gmail.com*/
select InvoiceNumber, InvoiceTotal

from Invoices
where PaymentTotal 
	> all 
	(
		Select top 50 percent PaymentTotal 
		from Invoices
		where InvoiceTotal - paymenttotal - credittotal  = 0
		order by PaymentTotal
	)
order by InvoiceTotal desc
