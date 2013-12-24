USE [MyGuitarShop]
GO
create proc spInsertCategory
	@CatName varchar(50)
as
		insert into Categories(CategoryName)
		values (@CatName);
	

GO

EXEC [dbo].[spInsertCategory] 'G%';


GO

EXEC [dbo].[spInsertCategory] 'hi';

GO 
