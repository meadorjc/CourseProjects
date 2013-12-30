/*Caleb Meador meadorjc at gmail.com*/
create proc spDateRange
	@DateMin varchar(50) = null,
	@DateMax varchar(50) = null
as
if @DateMin is null or @DateMax is null 
	throw 50001, 'The DateMin and DateMax parameters are required.', 1;
if not(ISDATE(@DateMin) = 1 and ISDATE(@DateMax) = 1)
	throw 50001, 'The format is not valid. Please use mm/d//yyyy.', 1;
if CAST(@DateMin as date)  > cast(@DateMax as date)
	throw 50001, 'The DateMin parameter must be earlier than DateMax),', 1;

select InvoiceNumber, InvoiceDate, InvoiceTotal,
		InvoiceTotal - CreditTotal - PaymentTotal as BalanceDue
from Invoices
where InvoiceDate between cast(@DateMin as datetime) and cast(@DateMax as datetime)
order by InvoiceDate