use AP;

update InvoiceCopy
set TermsID = 2
from InvoiceCopy  ic 
join VendorCopy vc 
on ic.VendorID = vc.VendorID
where DefaultTermsID = 2 ;