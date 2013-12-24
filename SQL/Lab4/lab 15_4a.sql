use MyGuitarShop;
if exists(select DB_ID('spInsertProduct'))
	drop procedure spInsertProduct;
go
create proc spInsertProduct
		@CatID int, 
		@ProdCode varchar(10), 
		@ProdName varchar(255), 
		@LPrice money, 
		@DiscPercent money
as 
	if @LPrice < 0 or @DiscPercent < 0
		throw 50001, 'Please check that both ListPrice and DiscountPercent are positive.', 1;
	else 
	begin
		insert into Products(CategoryID,
							ProductCode,
							ProductName,
							ListPrice,
							DiscountPercent,
							[Description],
							DateAdded)
		values (@CatID, @ProdCode, @ProdName, @LPrice, @DiscPercent, '', GETDATE());
	end;

go
exec [dbo].[spInsertProduct] 4, '1000', 'Hex-tech Rewinder', 450.00, 50.00;


go
exec [dbo].[spInsertProduct] 4, '1001', 'Void Staff of Stirring', -450.00, -50.00;
