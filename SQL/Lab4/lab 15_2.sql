/*Caleb Meador meadorjc at gmail.com*/
use MyGuitarShop;
go
/*scalar function means returns one regular value */
/*table value functions means that what gets returned
 by the function is a table */

if exists (select DB_ID('fnDiscountPrice'))
	drop function fnDiscountPrice;
go
create function fnDiscountPrice (@ItemIdDiscount int)
returns money 
begin
	declare @DiscountPrice money;
		
		select @DiscountPrice = oi.ItemPrice - oi.discountAmount
		from OrderItems oi
		where oi.ItemID = @ItemIdDiscount
	
	return @discountPrice
end;
go

select itemid, dbo.fnDiscountPrice(itemid) as discountprice
from orderitems;