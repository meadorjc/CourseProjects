/*Caleb Meador meadorjc at gmail.com*/
create view VendorAddress as 
	select VendorID, VendorAddress1, VendorAddress2, VendorCity, VendorState, VendorZipCode
	from Vendors
