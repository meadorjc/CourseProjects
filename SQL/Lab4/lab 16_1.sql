/*Caleb Meador meadorjc at gmail.com*/
use MyGuitarShop;

declare product_over_700 cursor
static
for
	select ProductName, format(listprice, '$, 0.00') as ListPrice
	from Products
	where listprice > 700
	order by listprice desc;

open product_over_700
fetch next from product_over_700;
while @@fetch_status = 0
	fetch next from product_over_700;
close product_over_700;
deallocate product_over_700;




