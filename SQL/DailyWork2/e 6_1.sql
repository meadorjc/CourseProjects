select distinct VendorName
from Vendors
where VendorID in (select VendorID from Invoices)
order by VendorName;
/* This query selects VendorIDs from Vendors where VendorID is the same in
 invoices, without pulling in both tables */