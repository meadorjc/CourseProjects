/*Caleb Meador meadorjc at gmail.com*/
USE MyGuitarShop;
if exists(select db_id('ProductsAudit'))
	drop table ProductsAudit;

go
select ProductID as AuditID
	, CategoryID
	, ProductCode
	, ProductName
	, ListPrice
	, DiscountPercent
	, DateAdded as DateUpdated
into ProductsAudit
from Products;

go

if exists(select db_id('Products_UPDATE'))
	drop trigger Products_UPDATE

go
create trigger Products_UPDATE
	on Products
	after update
as
	update ProductsAudit
	set CategoryID = (select categoryid from deleted),
		ProductCode= (select productcode from deleted),
		ProductName = (select productname from deleted),
		ListPrice = (select listprice	from deleted),
		DiscountPercent = (select discountpercent from deleted),
		dateupdated = getdate()
	where AuditID = (select productID from deleted);


go

--new update
update Products
set ProductCode = 'cat-tail',
	ProductName = 'Meownth Accordion',
	ListPrice = 15.0,
	DiscountPercent = 10
where ProductID = 1;


----old update
--update Products
--set ProductCode = 'bat-wing',
--	ProductName = 'Flapping Sonophone',
--	ListPrice = 50.00,
--	DiscountPercent = .5
--where ProductID = 1;

go

select * 
from products;

select *
from ProductsAudit
		
		
		
		
		




