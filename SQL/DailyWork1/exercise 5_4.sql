Use AP;
select AccountDescription,
COUNT(*) as LineItemCount,
SUM(InvoiceLineItemAmount) as LineItemSum
from GLAccounts as gla join InvoiceLineItems as ili
on gla.AccountNo = ili.AccountNo
group by AccountDescription
having COUNT(*) > 1
order by LineItemCount desc;