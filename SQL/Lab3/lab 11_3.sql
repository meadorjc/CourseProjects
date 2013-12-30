/*Caleb Meador meadorjc at gmail.com*/
use Test_MyWebDB;

insert  Users 
values ('hi@bye.com', 'Jimmy', 'Dean'),
('say@what.edu', 'Hootie', 'Blowfish');

insert Products
values ('Harley-Davidson WindChime'),
('TollHouse Cookie Monster');

insert Downloads
values (1, GETDATE(), 'hdwc.zip', 1),
(2, GETDATE(), 'hdwc.zip', 1),
(2, GETDATE(), 'thcm.zip', 2);



select EmailAddress, FirstName, LastName,
	DownloadDate, [FileName], ProductName
from Users join Downloads
on users.UserID = downloads.UserID
join Products on products.ProductID = Downloads.ProductID;



