select AccountNo, 
	SUM(InvoiceLineItemAmount) as TotalAmount

from InvoiceLineItems
group by AccountNo with rollup;
