/*Caleb Meador meadorjc at gmail.com*/
/* What's the advantage of a stored procedure? 
	 Same advantage as a view: Its compiled in machine language,
	 as are functions and triggers. Therefore, they run faster.
	 If there are a lot of operations, it can speed up the run
	 time of your system.

	 Though, not good for complex procedures. C++ can build complex
	 procedures using .NET.
*/
Use AP;

go
create proc spBalanceRange 
	@VendorVar varchar(50) = '%',		/* ORACLE uses ':' instead of '@' */
	@BalanceMin money = 0,				/* if uninitialized, assumed 0 */
	@BalanceMax money = 0
as
	if @BalanceMax = 0
	begin
		select VendorName, InvoiceNumber,
				InvoiceTotal - CreditTotal - PaymentTotal as Balance
		from Vendors v join invoices i
		on v.VendorID = i.VendorID
		where InvoiceTotal - CreditTotal - PaymentTotal > 0  and 
				InvoiceTotal - CreditTotal - PaymentTotal >=@BalanceMin and 
				VendorName like @VendorVar
		order by Balance desc
	end;
	
	else 
	begin
		select VendorName, InvoiceNumber, InvoiceTotal-CreditTotal-PaymentTotal as Balance
		from Vendors join Invoices on Vendors.VendorID = Invoices.VendorID
		where InvoiceTotal - CreditTotal - PaymentTotal > 0 and VendorName like @VendorVar
		and InvoiceTotal-CreditTotal-PaymentTotal between @BalanceMin and @BalanceMax
		order by Balance 
	end;
