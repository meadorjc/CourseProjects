use AP;

select InvoiceNumber,InvoiceDate,InvoiceTotal,
InvoiceLineItemDescription as ItemDescription,
InvoiceLineItemAmount as ItemAmount
from Invoices i join InvoiceLineItems ili
on i.InvoiceID = ili.InvoiceID
where i.InvoiceID in (select Invoices.InvoiceID
from Invoices join InvoiceLineItems 
on Invoices.InvoiceID = InvoiceLineItems.InvoiceID
group by Invoices.InvoiceID
having count(InvoiceLineItemDescription) > 1)
order by InvoiceDate
for xml auto,root ('MultipleLineItems'), ELEMENTS;