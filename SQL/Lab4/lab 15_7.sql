/*Caleb Meador meadorjc at gmail.com*/
use MyGuitarShop;

if exists (select db_id('Products_INSERT'))
	drop trigger Products_INSERT;
go

create trigger Products_INSERT 
	on Products
	after insert
as
	--if (select dateadded from inserted) = NULL --why doesn't if statment work?
		update products
		set DateAdded = (getdate())
		where productID = (select productID from inserted);

go

insert into products (ProductCode, ProductName, Description, ListPrice, DiscountPercent)
values ('banjo5', 'Chuckie Cheese Banjo', 'Rockin Rollin Good-Times Banjo', 1.00, 5.00);

go

select *
from Products
