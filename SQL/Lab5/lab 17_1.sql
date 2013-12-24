use MyGuitarShop;
begin try
	begin tran;
		delete Addresses 
		where customerID = 8
		delete customers
		where CustomerID = 8
	commit tran;
end try
begin catch
	rollback tran;
end catch

