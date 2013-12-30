/*Caleb Meador meadorjc at gmail.com*/
select vendor_name, 
		upper(vendor_name), 
		substring(vendor_phone,11, 4),
		concat(substring(vendor_phone, 2, 3),
		'.', substring(vendor_phone,7, 3),
		'.', substring(vendor_phone, 11, 4)) as phone_number,
		case 
			when locate(' ', vendor_name) = 0 then ' '
			else substring_index(substring_index(vendor_name, ' ', 2), ' ', -1)
		end as short_vendor_name
from vendors