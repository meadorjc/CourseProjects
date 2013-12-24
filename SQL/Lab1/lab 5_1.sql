/*1.	Write a SELECT statement that returns these columns:
The count of the number of orders in the Orders table
The sum of the TaxAmount columns in the Orders table
*/

use MyGuitarShop;

select count(*) as "Count", sum(TaxAmount) as "Total Tax Amount"
from Orders;