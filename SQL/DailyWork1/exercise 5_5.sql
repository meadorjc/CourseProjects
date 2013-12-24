Use AP;
select AccountDescription,
COUNT(*) as LineItemCount,
SUM(InvoiceLineItemAmount) as LineItemSum
from GLAccounts as gla join InvoiceLineItems as ili
on gla.AccountNo = ili.AccountNo
join Invoices as i 
on ili.InvoiceID = i.InvoiceID
where InvoiceDate between '2011-12-01' and '2012-02-29'
group by AccountDescription
having COUNT(*) > 1
order by LineItemCount desc;
