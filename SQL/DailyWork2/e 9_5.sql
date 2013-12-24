
select invoicenumber, 
invoicetotal-paymenttotal-CreditTotal as BalanceDue,
RANK() over (order by invoicetotal-paymenttotal-CreditTotal desc) as BalanceRank
from Invoices
where InvoiceDueDate < getdate() + 30 and invoicetotal-paymenttotal-CreditTotal > 0