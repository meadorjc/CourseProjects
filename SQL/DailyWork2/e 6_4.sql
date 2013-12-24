Select AccountNo, AccountDescription

from glaccounts as gla
where Not Exists ( select * from InvoiceLineItems as ili
					where gla.AccountNo = ili.AccountNo
				  )

order by AccountNo;
