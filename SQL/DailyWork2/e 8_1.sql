/*Caleb Meador meadorjc at gmail.com*/
use AP;

select 
Cast(InvoiceTotal as decimal(18,2)) as cast2decimal, 
Cast(invoiceTotal as varchar) as cast2varchar,
CONVERT(decimal(18, 2), InvoiceTotal) as convertdec,
CONVERT(varchar, invoicetotal, 1) as convertvar
from Invoices