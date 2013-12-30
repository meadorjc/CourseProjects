/*Caleb Meador meadorjc at gmail.com*/
select InvoiceNumber, InvoiceTotal
from invoices
where PaymentTotal > (select AVG(PaymentTotal) 
from Invoices
where (InvoiceTotal - PaymentTotal - CreditTotal) = 0)
order by InvoiceTotal desc;