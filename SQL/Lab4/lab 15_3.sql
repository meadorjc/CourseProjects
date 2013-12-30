/*Caleb Meador meadorjc at gmail.com*/
use MyGuitarShop;
go
/*scalar function means returns one regular value */
/*table value functions means that what gets returned
 by the function is a table */

if exists (select DB_ID('fnItemTotal'))
	drop function fnItemTotal;
go
create function fnItemTotal (@ItemIdDiscount int)
returns money 
begin
	declare @TotalItemAmount money;
		
		select @TotalItemAmount = dbo.fnDiscountPrice(ItemID)*oi.Quantity
		from OrderItems oi
		where oi.ItemID = @ItemIdDiscount
	
	return @TotalItemAmount
end;
go

select itemid, dbo.fnDiscountPrice(itemid) as discountprice, dbo.fnItemTotal(itemid) as ItemTotal
from orderitems;