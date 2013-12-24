select Vendorname, FunctionTable.*
from vendors join invoices on vendors.vendorID = invoices.vendorid
join dbo.fnDateRange('12/10/2011', '12/20/2011')
as FunctionTable
on Invoices.InvoiceNumber = FunctionTable.InvoiceNumber