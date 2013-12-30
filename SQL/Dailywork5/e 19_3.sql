/*Caleb Meador meadorjc at gmail.com*/
use ap;

declare @contactupdatehandle int;
declare @contactupdates xml;

set @contactupdates = '
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
exec sp_Xml_PrepareDocument @ContactUpdateHandle output,
@ContactUpdates;   

select * 
from OPENXML (@contactupdatehandle, '/ContactUpdates/Contact')
with
(
	VendorID	int				'@VendorID',
	FirstName	varchar(50)		'FirstName',
	LastName	varchar(50)		'LastName'
);

exec sp_xml_RemoveDocument @ContactUpdateHandle;

