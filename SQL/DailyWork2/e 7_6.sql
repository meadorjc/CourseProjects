use AP;

update InvoiceCopy
set TermsID = 2
where VendorID in 
(select VendorID
from VendorCopy
where DefaultTermsID = 2)

