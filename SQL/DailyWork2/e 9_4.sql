use ap;
select 
	case 
		when grouping(AccountDescription) = 1
		then '*ALL*'
		else AccountDescription
	end as Account,
	case 
		when grouping(VendorState) = 1
		then '*ALL*'
		else VendorState
	end as State,
	SUM(InvoiceLineItemAmount) as LineItemSum
from Vendors v 
join Invoices i
on v.vendorid = i.vendorid
join invoicelineitems ili
on i.invoiceID = ili.InvoiceID
join glaccounts gla
on gla.AccountNo = ili.AccountNo
group by AccountDescription, VendorState with cube