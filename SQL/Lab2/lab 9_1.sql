use MyGuitarShop;

select listprice, discountpercent, 
		round((listprice*discountpercent*.01), 2) as DiscountAmount
from Products;
