/*Caleb Meador meadorjc at gmail.com*/
select *
from dbo.fnDateRange('03/01/2012','03/31/2013')
where Balance > 0
order by Balance desc