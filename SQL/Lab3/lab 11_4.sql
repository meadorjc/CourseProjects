use Test_MyWebDB;

Alter table products
	add ProductPrice DECIMAL(3,2) NOT NULL DEFAULT(9.99);

Alter table Products
	add ProductAddDate datetime null;


