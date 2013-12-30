/*Caleb Meador meadorjc at gmail.com*/
use AP;

select cast(InvoiceDate as varchar) as date2var,
		convert(varchar, invoicedate, 1) as date2var1,
		convert(varchar, invoicedate, 10) as date2var10,
		cast(invoicedate as real) as date2real
from Invoices