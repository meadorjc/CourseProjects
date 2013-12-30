/*Caleb Meador meadorjc at gmail.com*/
create trigger Invoices_UPDATE_Shipping
	on Invoices
	after insert, update
as
	insert ShippingLabels
	select VendorName, VEndorAddress1, VendorAddress2, 
	VendorCity, VendorState, VendorZipCode 
	from Vendors join inserted /*inserted means 'seen a change'*/
	on vendors.vendorID = (select VendorID from inserted)
	where inserted.InvoiceTotal - inserted.CreditTotal - inserted.PaymentTotal = 0;