/* a correlated table is one where x.table = y.table */
select vendor_name, 
		invoice_number,
		invoice_date,
		invoice_total
from invoices i 
join vendors v
on i.vendor_id = v.vendor_id
where invoice_date = (select MIN(invoice_date)
						from invoices
						where vendor_id = i.vendor_id)
order by vendor_name;