/*Caleb Meador meadorjc at gmail.com*/
create function fnDateRange
	(@DateMin smalldatetime, @DateMax smalldatetime)
returns table
return 
	(select InvoiceNumber, InvoiceDate, InvoiceTotal,
		InvoiceTotal-CreditTotal-PaymentTotal as Balance
	from Invoices
	where InvoiceDate between @DateMin and @DateMax);

