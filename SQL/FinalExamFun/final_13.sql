/*Caleb Meador meadorjc at gmail.com*/
use Halloween;


Create TABLE ProductImages (
		ImageID int primary key identity,
		productid varchar(20),
		ImageProduct varbinary(max)
)