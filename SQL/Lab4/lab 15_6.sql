create trigger Products_UPDATE 
	on Products
	after update
as 
	if exists
	(select inserted.discountpercent
	from inserted) 
	BEGIN 
		if exists 
		(select inserted.discountpercent
		from inserted 
		where (inserted.discountpercent < 0 or inserted.discountpercent > 100))
		BEGIN
			throw 50001, 'Discount percent must be between 0 and 100', 1;
			ROLLBACK TRAN;
		END;

		if exists
		(select i.discountpercent
		from inserted as i join products p
		on i.ProductID = p.ProductID
		where (i.discountpercent > 0 and i.discountpercent < 1))
		BEGIN
			update Products 
			set products.discountpercent = (select discountpercent*100 from inserted)
			where  products.ProductID IN(select ProductID from inserted)
			END;
	END;
