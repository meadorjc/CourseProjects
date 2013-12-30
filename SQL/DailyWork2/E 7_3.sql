/*Caleb Meador meadorjc at gmail.com*/
INSERT into VendorCopy
		(VendorName,
		VendorAddress1, 
		VendorAddress2, 
		VendorCity, 
		VendorState, 
		VendorZipCode,
		VendorPhone, 
		VendorContactLName, 
		VendorContactFName, 
		DefaultTermsID, 
		DefaultAccountNo)
select VendorName, 
		VendorAddress1, 
		VendorAddress2, 
		VendorCity, 
		VendorState, 
		VendorZipCode,
		VendorPhone, 
		VendorContactLName, 
		VendorContactFName, 
		DefaultTermsID, 
		DefaultAccountNo 
 from Vendors
where VendorState <> 'CA';