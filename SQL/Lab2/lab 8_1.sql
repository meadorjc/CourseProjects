use myguitarshop;

select Listprice, cast(listprice as decimal(19,1)), convert(integer, listprice), cast(listprice as integer)
from Products