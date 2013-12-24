create login AAaron with password = 'aaar9999',
default_Database = AP;

/*user == login ok? yes*/
create user Aaron for login AAaron;

alter role PaymentEntry add member AAaron;

