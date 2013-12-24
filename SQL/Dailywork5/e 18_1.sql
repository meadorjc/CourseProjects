use AP;

create role PaymentEntry;
grant update
on Invoices
to PaymentEntry;

grant insert, update
on invoicelineitems
to paymententry;

alter role db_datareader add MEMBER PaymentEntry;

