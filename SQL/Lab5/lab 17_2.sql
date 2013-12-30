/*Caleb Meador meadorjc at gmail.com*/
use MyGuitarShop;
go
declare  @orderid int;
begin try
	begin tran;
		

		insert orders
		values(3, getdate(), '10.00', '0.00', NULL, 4, 
			'American Express', '378282246310005', '04/2013', 4);

		set @orderID = @@IDENTITY;

		insert orderitems
		values (@orderID, 6, '415.00', '161.85', 1);

		insert orderitems
		values (@orderID, 1, '699.00', '209.70', 1);
		commit tran;
	end try
	begin catch
		rollback tran;
	end catch