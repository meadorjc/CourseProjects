/*Caleb Meador meadorjc at gmail.com*/
	use ap;
	go

	begin try
		begin tran;
			
		insert into InvoiceArchive
			select *
			from Invoices
			where InvoiceTotal - PaymentTotal - CreditTotal = 0 and
			InvoiceID not in (select invoiceID from InvoiceArchive)
			/*just copy what's in invoices; now need delete statement */

			delete invoices where InvoiceID in (select invoiceID from InvoiceArchive)
		commit tran;
	end try
	begin catch
		rollback tran;
	end catch