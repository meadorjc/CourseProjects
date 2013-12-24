use myguitarshop;

create login RobertHalliday with password = 'HelloBob',
default_database = MyGuitarShop;

create user RobertHalliday;

alter role OrderEntry add member RobertHalliday;

