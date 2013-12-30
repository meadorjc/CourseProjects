/*Caleb Meador meadorjc at gmail.com*/
USE COLLEGE;

SELECT * 
	FROM STUDENT
	FOR XML AUTO, ROOT('STUDENT'), ELEMENTS; 