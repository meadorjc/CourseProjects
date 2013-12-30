/*Caleb Meador meadorjc at gmail.com*/
alter table users
	alter column firstname varchar(20) not null;

update users set FirstName = null;

update users set FirstName = 'Supercalifragilisticexpialidocious';