/*Caleb Meador meadorjc at gmail.com*/
/* derived table example*/
select SUM(max_invoice_total) as sum_max_invoice_total
from 
	( /*this acts as a table; a derived table*/	
		select vendor_id, 
				 max(invoice_total)
		as max_invoice_total
		from invoices
		where 
		  invoice_total - payment_total - credit_total > 0
		group by vendor_id
	
	) max_invoice 
		