/*Caleb Meador meadorjc at gmail.com*/
select VendorID, SUM(PaymentTotal) 
as PaymentSum
from Invoices
group by VendorID;
