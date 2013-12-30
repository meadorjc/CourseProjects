/*Caleb Meador meadorjc at gmail.com*/
use ap;

Alter table Invoices 
	add check ((PaymentDate is null and PaymentTotal = 0) 
	or (PaymentDate is not null and PaymentTotal > 0)),
	check ((PaymentTotal+CreditTotal) <=  InvoiceTotal)


