use MyGuitarShop;

declare @newcustomer xml;

set @newcustomer = 
'<NewCustomers>
	<Customer EmailAddress="izzychan@yahoo.com" Password="" FirstName="Isabella" LastName="Chan" />
	<Customer EmailAddress="johnprine@gmail.com" Password="" FirstName="John" LastName="Prine" />
	<Customer EmailAddress="kathykitchen@sbcglobal.net" Password="" FirstName="Kathy" LastName="Kitchen" />
</NewCustomers>';

declare @newcustomershandle int;

exec sp_xml_prepareDocument @newnewcustomershandle output, @newcustomers;

select* from openxml (@newcustomershandle, '/newcustomers/customer')
with (
	emailaddress varchar(50) '@emailaddress',
	password	 varchar(50) '@password',
	firstname	 varchar(50) '@firstname',
	lastname	 varchar(50) '@lastname'
);

exec sp_xml_removedocument @newcustomershandle;

