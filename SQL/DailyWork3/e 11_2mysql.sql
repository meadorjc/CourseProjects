/*Caleb Meador meadorjc at gmail.com*/
/*mySQL uses autoincrement to denote primary key:
	SQL uses identity */

/*drop the tables that have the foreign keys first */
drop table if exists members_groups;
drop table if exists members;
drop table if exists groups;

use ex;

create table members
(
	member_id int primary key auto_increment,
	first_name varchar(20) not null,
	last_name varchar(20) not null,
	address varchar(50) not null,
	city varchar(30) not null,
	state char(2) not null,
	phone varchar(14)
	
);

create table groups
(
	group_id int primary key auto_increment,
	group_name varchar(50) not null
);

create table members_groups
(
	member_id int not null,
	group_id int not null,
	constraint members_groups_fk_members foreign key (member_id) 
		references members(member_id),
	constraint members_groups_fk_groups foreign key (group_id)
		references groups(group_id)
);
