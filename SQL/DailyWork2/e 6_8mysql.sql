/*Caleb Meador meadorjc at gmail.com*/
/* here must use an inline view instead
	of a correlated subquery
*/
select vendor_name, 
		invoice_number,
		invoice_date,
		invoice_total
from invoices i
join (  /*this statement acts as a table: aka, an inline view*/
		select vendor_id, min(invoice_date) 
		as oldest_invoice_date
		from invoices 
		group by vendor_id
	 ) oi
on i.vendor_id = oi.vendor_id
and oi.oldest_invoice_date = i.invoice_date
join vendors v 
on i.vendor_id = v.vendor_id
order by vendor_name;




/* alternate code for same results

vendors v
on i.vendor_id = v.vendor_id
where invoice_date = (select MIN(invoice_date)
						from invoices
						where vendor_id = i.vendor_id)
order by vendor_name;*/