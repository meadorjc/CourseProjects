/*Caleb Meador meadorjc at gmail.com*/
select invoice_total, ROUND(invoice_total, 1), 
ROUND(invoice_total, 0)
from invoices 