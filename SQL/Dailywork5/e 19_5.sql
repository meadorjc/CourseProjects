/*Caleb Meador meadorjc at gmail.com*/
use AP;

create table ProductImages (
ImageID int primary key identity,
ProductID int not null,
ProductImage varbinary(max)
);

insert into ProductImages values  (1, NULL);

insert into ProductIMages values (2,0);

insert into ProductImages values (3, cast('0123456789ABCDEF' as varbinary));
