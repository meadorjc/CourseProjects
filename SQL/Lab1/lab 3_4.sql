select ProductName, 
	ListPrice,	
	DiscountPercent, 
	DiscountPercent*(ListPrice/100) as DiscountAmount,
	ListPrice - (DiscountPercent*(ListPrice/100)) as DiscountPrice
from Products
order by DiscountPrice desc;