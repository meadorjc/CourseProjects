select gla.AccountNo, AccountDescription
from GLAccounts as gla 
left join InvoiceLineItems as ili
on gla.AccountNo = ili.AccountNo
where ili.AccountNo is null
order by gla.AccountNo;
