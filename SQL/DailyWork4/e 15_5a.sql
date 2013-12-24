use AP;
go
/*scalar function means returns one regular value */
/*table value functions means that what gets returned
 by the function is a table */


create function fnUnpaidInvoiceID() 
returns int 
begin
	return
	(select MIN(InvoiceID) from Invoices
	where (InvoiceTotal-CreditTotal-PaymentTotal) > 0
	and InvoiceDueDate = 
		(select min(InvoiceDueDate) from Invoices
		where (InvoiceTotal-CreditTotal-PaymentTotal) > 0))
end;