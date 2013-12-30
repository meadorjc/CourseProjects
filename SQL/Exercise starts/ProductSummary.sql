/*Caleb Meador meadorjc at gmail.com*/
SELECT COUNT(*) AS NumberOfProducts,
       MAX(ListPrice) AS MostExpensiveProduct,
       MIN(DateAdded) AS OldestProduct
FROM Products