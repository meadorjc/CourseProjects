/*Caleb Meador meadorjc at gmail.com*/
use ap;
select VendorID, 
	InvoiceDate, 
	InvoiceTotal,
	SUM(InvoiceTotal) over (partition by VendorID) as VendorTotal,
	COUNT(InvoiceID) over (partition by VendorID) as VendorCount,
	AVG(InvoiceTotal) over (partition by VendorID) as VendorAvg
from Invoices