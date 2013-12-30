/*Caleb Meador meadorjc at gmail.com*/
use AP;
select VendorName, VendorState
from Vendors
where VendorState = 'CA'
union
select VendorName, 'Outside CA' as VendorState
from Vendors
where VendorState <> 'CA'
order by VendorName;