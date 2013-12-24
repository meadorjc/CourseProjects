use ap;
/*to declare a parameter! no normal variables!*/
declare @TotalBalanceDue money; 

select @TotalBalanceDue = 
	SUM(InvoiceTotal-CreditTotal-PaymentTotal)
from Invoices
where (InvoiceTotal-CreditTotal-PaymentTotal) > 0;
/*return only rows where a balance is due*/

if @TotalBalanceDue > 10000
	select VendorName, InvoiceNumber, InvoiceDueDate,
	InvoiceTotal-CreditTotal-PaymentTotal as Balance
	from Invoices i join Vendors v
	on i.VendorID = v.VendorID
	where InvoiceTotal-CreditTotal-PaymentTotal >0
	order by InvoiceDueDate;
else
	print 'Balance due is less than $10,000.00';