/*Caleb Meador meadorjc at gmail.com*/
use AP;
begin try
	begin tran;
		update Invoices set VendorID = 123	/*vendorID for UPS */
		where VendorID = 122				/*vendorID for FedExp */
		update VEndors set VendorName = 'FedUp'
		where VendorID = 123
		delete Vendors where VendorId = 122
		and VendorName = 'United Parcel Service'
	commit tran;
end try
begin catch
	rollback tran;
end catch