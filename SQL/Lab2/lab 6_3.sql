select CategoryName 
from Categories
where NOT EXISTS (select *
					from Products
					where Products.CategoryID
					= Categories.CategoryID)