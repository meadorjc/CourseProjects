select * from InvoiceBasic 
where VendorName like '[N-P]%' /*(left(VendorName, 1) = 'N'or left(vendorName, 1) = 'O' or left(vendorName, 1) = 'N')*/
order by VendorName

/* a view is used to substitute for a table that is tedious to type all the time 
	especially when its used all the time */