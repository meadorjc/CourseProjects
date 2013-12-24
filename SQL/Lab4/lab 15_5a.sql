use MyGuitarShop;
if exists(select DB_ID('spUpdateProductDiscount'))
	drop procedure spUpdateProductDiscount;
go
create proc spUpdateProductDiscount
		@ProdID int, 
		@DiscPercent money
as 
	if @DiscPercent < 0
		throw 50001, 'Please check that DiscountPercent is positive.', 1;
	else 
	begin
		update Products
		set DiscountPercent = @DiscPercent
		where ProductID = @ProdID
	end;

go
exec [dbo].[spUpdateProductDiscount] 1, 99.00;
go
exec [dbo].[spUpdateProductDiscount] 1, -99.00;