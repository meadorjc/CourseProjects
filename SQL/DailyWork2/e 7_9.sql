/*Caleb Meador meadorjc at gmail.com*/
use AP;

delete VendorCopy
where VendorState not in
(select Distinct VendorState
from VendorCopy vc
join invoicecopy ic
on vc.VendorID=ic.VendorID)
