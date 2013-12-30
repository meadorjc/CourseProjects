/*Caleb Meador meadorjc at gmail.com*/
select LastName + ', ' + FirstName as FullName
from Customers
where LEFT(Lastname, 1) >= 'M'
order by LastName asc;

