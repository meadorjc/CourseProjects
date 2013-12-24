Select ProductName, DiscountPercent
from Products
WHERE DiscountPercent NOT IN (
	SELECT DiscountPercent
	from Products
	GROUP BY DiscountPercent
	Having count(DiscountPercent) > 1)
Order by ProductName;