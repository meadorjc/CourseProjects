use MyGuitarShop;

create role OrderEntry;

grant Insert, update 
on orders
to orderentry;

grant Insert, update 
on orderitems
to orderentry;

grant select
to orderentry;

alter role db_datareader add MEMBER orderEntry;


