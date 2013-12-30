/*Caleb Meador meadorjc at gmail.com*/
use AP;

begin try
	exec spDateRange '2011-12-10', '2011-12-20';
end try
begin catch
	print 'Error Number: ' + Convert(varchar(100), ERROR_NUMBER());
	print 'Error Message: ' + Convert(varchar(100), ERROR_MESSAGE());
end catch