create or replace view open_items as
	select vendor_name, invoice_number, invoice_total, 
			invoice_total-credit_total-payment_total as balance_due
	from vendors v join invoices i
	on v.vendor_id = i.vendor_id
	where invoice_total-credit_total-payment_total > 0
	order by vendor_name;