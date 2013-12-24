use AP;
GO
declare @contactupdate xml;
set @ContactUpdate = '
<ContactUpdates>
	<Contact VendorID="4">
		<LastName>McCrystle</LastName>
		<FirstName>Timothy</FirstName>
	</Contact>
	<Contact VendorID="10">
		<LastName>Flynn</LastName>
		<FirstName>Erin</FirstName>
	</Contact>
</ContactUpdates>
'
;
update Vendors 
set VendorContactLName = @ContactUpdate.value('(/ContactUpdates/Contact/LastName)[1]','varchar(50)'),
VendorContactFName = @ContactUpdate.value('(/ContactUpdates/Contact/FirstName)[1]','varchar(50)')
where VendorID = @ContactUpdate.value('(/ContactUpdates/Contact/@VendorID)[1]','int');
update Vendors 
set VendorContactLName = @ContactUpdate.value('(/ContactUpdates/Contact/LastName)[2]','varchar(50)'),
VendorContactFName = @ContactUpdate.value('(/ContactUpdates/Contact/FirstName)[2]','varchar(50)')
where VendorID = @ContactUpdate.value('(/ContactUpdates/Contact/@VendorID)[2]','int');

GO
select VendorID,VendorContactLName,VendorContactFName
from Vendors
where VendorID = 4 or VendorID = 10;