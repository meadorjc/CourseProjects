/*Caleb Meador meadorjc at gmail.com*/
Update InvoiceCopy
set PaymentDate = GetDate(),
	PaymentTotal = InvoiceTotal - CreditTotal - PaymentTotal
where InvoiceTotal - CreditTotal - PaymentTotal > 0;
