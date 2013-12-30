/*Caleb Meador meadorjc at gmail.com*/
/*e6-6 mySQL
	In mySQL, the databases are not capitalized
	concat() must be used in mySQL; SQL can use '+' or concat() to concatenate 
*/

select vendor_name, 
		vendor_city, 
		vendor_state
from vendors
where concat(vendor_state, vendor_city)
not in 
	(select concat(vendor_state, vendor_city)
	 as vendor_state_city
	 from vendors
	 group by vendor_state_city
	 having count(*) > 1)
order by vendor_state, vendor_city;




