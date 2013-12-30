/*Caleb Meador meadorjc at gmail.com*/
select v1.VendorID, v1.VendorName,
v1.VendorContactFName + ' ' + v1.VendorContactLName 
as Name
from Vendors as v1 join Vendors as v2
on (v1.VendorID <> v2.VendorID) and
(v1.VendorContactFName = v2.VendorContactFName)
order by Name;